#include "cScene.hpp"
#include "Globals.hpp"
#include "cEnemy.hpp"
#include "cExplosion.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <iostream>
#include "cNormalShip.hpp"
#include "cWalkingBomb.hpp"
#include "cPlayer.hpp"

cScene::cScene() : CoordChanges(), Player(*this, CoordChanges), mExitDoor(*this, CoordChanges, Player),
 mInterruptor(*this, CoordChanges, Player, mExitDoor) {}
cScene::~cScene() {}

bool cScene::Init() {
	//Player initialization
	Player.Init();
	Player.SetWidthHeight_W(40,40);
	Player.SetPosition_T(Vec3(2,1)); //Initial tile

  mExitDoor.Init();
  mExitDoor.SetWidthHeight_W(32,32);
  mInterruptor.Init();
  mInterruptor.SetWidthHeight_W(32,32);
  
	//Enemy initialization
	//mEnemies.push_back(new cNormalShip(Scene, CoordChanges, 1, Vec3(15, 17), true));
	mEnemies.push_back(new cNormalShip(Player, *this, CoordChanges, 1, Vec3(22, 22), true));
	mEnemies.push_back(new cWalkingBomb(*this, CoordChanges, 1, Vec3(35, 1), true, Player));

  return mText.Load("blocks.png",GL_RGBA);
}
bool cScene::LoadLevel(int level) {
  // get filename
  std::stringstream stream;
  stream << "level";
  if(level<10) stream << "0";
  stream << level << ".txt";
  std::string file = stream.str();
  
  //open file and get dimensions
  std::fstream fd(file);
  if(!fd) return false;
  unsigned int scene_width, scene_height;
  fd >> scene_width >> scene_height;
  { char c;
  fd.get(c); }

  //resize map
  map.resize(scene_width);
  std::for_each(map.begin(), map.end(), [&scene_height](std::vector<int>&v) {
	  v.resize(scene_height); });

  id_DL=glGenLists(1);
  glNewList(id_DL,GL_COMPILE);
  glBegin(GL_QUADS);
	
  int px,py;
  for(int j=scene_height-1;j>=0;j--) {
	char tile;
	px=CoordChanges.getOriginX();
	py=CoordChanges.getOriginY()+(j*CoordChanges.GetTileSize());

    for(unsigned int i=0;i<scene_width;i++) {
	  fd.get(tile);
	  if(tile==' ') {
	      //Tiles must be != 0 !!!
	      map[i][j]=0;
	  } else {
	      //Tiles = 1,2,3,...
	      map[i][j] = tile-48;//'0'
		  
	      float coordx_tile, coordy_tile;
	      if(map[i][j]%2) coordx_tile = 0.0f;
	      else						 coordx_tile = 0.5f;
	      if(map[i][j]<3) coordy_tile = 0.0f;
	      else						 coordy_tile = 0.5f;

	      //BLOCK_SIZE = 24, FILE_SIZE = 64
	      // 24 / 64 = 0.375
	      glTexCoord2f(coordx_tile       ,coordy_tile+0.375f);	glVertex2i(px           ,py           );
	      glTexCoord2f(coordx_tile+0.375f,coordy_tile+0.375f);	glVertex2i(px+CoordChanges.getBlockSize(),py           );
	      glTexCoord2f(coordx_tile+0.375f,coordy_tile       );	glVertex2i(px+CoordChanges.getBlockSize(),py+CoordChanges.getBlockSize());
	      glTexCoord2f(coordx_tile       ,coordy_tile       );	glVertex2i(px           ,py+CoordChanges.getBlockSize());
	  }
	  px+=CoordChanges.GetTileSize();
	}
	fd.get(tile);//pass enter
  }

  glEnd();
  glEndList();

  unsigned int obstacles;
  fd >> obstacles;
  mObstacles.clear();
  mObstacles.reserve(obstacles);
  for(unsigned int i=0; i<obstacles; ++i) {
	  mObstacles.push_back(cObstacle(*this, CoordChanges));
	  fd >> mObstacles[i];
	  mObstacles[i].Init();
	  mObstacles[i].SetWidthHeight_W(24,24);///TODO Extract from the texture automagically.
  }
  float puerta_tile_x, puerta_tile_y;
  fd >> puerta_tile_x >> puerta_tile_y;
  mExitDoor.SetPosition_T(Vec3(puerta_tile_x, puerta_tile_y,0));
  fd >> puerta_tile_x >> puerta_tile_y;
  mInterruptor.SetPosition_T(Vec3(puerta_tile_x, puerta_tile_y,0));
  fd.close();

  return true;
}

void cScene::Draw(float const t, float const dt) const {
  int tex_id = mText.GetID();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,tex_id);
  glCallList(id_DL);
  glDisable(GL_TEXTURE_2D);
  std::for_each(mObstacles.begin(), mObstacles.end(), [&](cObstacle const& obs){
	  obs.Draw(t, dt);});
  mExitDoor.Draw(t,dt);
  mInterruptor.Draw(t,dt);
	Player.Draw(t,dt);
	
	for (size_t i = 0; i < mEnemies.size(); ++i) {
		mEnemies[i]->Draw(t,dt);
	}
  for(auto& expl: mExplosions)
    expl.Draw(t,dt);
}
void cScene::doLogic(float const t, float const dt) {
	Player.doLogic(t,dt);
  mExitDoor.doLogic(t,dt);
  mInterruptor.doLogic(t,dt);

  for(std::vector<cEnemy*>::iterator it = mEnemies.begin(); it!=mEnemies.end();) {
    (*it)->doLogic(t,dt);
    if ( (*it)->WantsToDestroyItself())
      it = mEnemies.erase(it);
    else it++;
  }
  for(std::vector<cExplosion>::iterator it = mExplosions.begin(); it!=mExplosions.end();) {
    if (it->hasFinished(t) || it->WantsToDestroyItself()) {
    //std::cout << "Una explosion menos";
      it = mExplosions.erase(it);
    }
    else it++;
  }
}
bool cScene::CollisionInClosedArea(cRect const& world) const {
  Vec3 const tile0 = CoordChanges.WorldToTile(Vec3(world.left , world.bottom, 0));
  Vec3 const tile1 = CoordChanges.WorldToTile(Vec3(world.right, world.top   , 0));

  ///Scenery
  for(int i=tile0.x; i<=tile1.x; ++i) {
    for(int j=tile0.y;j<=tile1.y;j++)	{
      if(operator()(i, j) != 0)  return true;
    }
  }

  ///Obstacles
  for(auto it = mObstacles.begin(); it!=mObstacles.end(); ++it) {
	  if(it->GetBBox().collides(world))
		  return true;
  }

  ///Other
  return false;
}
