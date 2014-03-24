#include "cScene.hpp"
#include "Globals.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <assert.h>


cScene::cScene(cCoordChanges const& cc) : mCoordChanges(cc) {}
cScene::~cScene() {}

bool cScene::Init() {
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
	px=mCoordChanges.getOriginX();
	py=mCoordChanges.getOriginY()+(j*mCoordChanges.GetTileSize());

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
	      glTexCoord2f(coordx_tile+0.375f,coordy_tile+0.375f);	glVertex2i(px+mCoordChanges.getBlockSize(),py           );
	      glTexCoord2f(coordx_tile+0.375f,coordy_tile       );	glVertex2i(px+mCoordChanges.getBlockSize(),py+mCoordChanges.getBlockSize());
	      glTexCoord2f(coordx_tile       ,coordy_tile       );	glVertex2i(px           ,py+mCoordChanges.getBlockSize());
	  }
	  px+=mCoordChanges.GetTileSize();
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
	  mObstacles.push_back(cObstacle(*this, mCoordChanges));
	  fd >> mObstacles[i];
	  mObstacles[i].Init();
	  mObstacles[i].SetWidthHeight_W(24,24);///TODO Extract from the texture automagically.
      mObstacles[i].SetState(STATE_LOOKRIGHT);
  }
  fd.close();

  return true;
}

void cScene::Draw() const {
  int tex_id = mText.GetID();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,tex_id);
  glCallList(id_DL);
  glDisable(GL_TEXTURE_2D);
  std::for_each(mObstacles.begin(), mObstacles.end(), [&](cObstacle const& obs){
	  obs.Draw();});
}
bool cScene::CollisionInClosedArea(int const x0, int const x1, int const y0, int const y1) const {
  ///Scenery
  for(int i=x0; i<=x1; ++i) {
    for(int j=y0;j<=y1;j++)	{
      if(operator()(i, j) != 0)  return true;
    }
  }
  ///Obstacles
  for(auto it = mObstacles.begin(); it!=mObstacles.end(); ++it) {
	  if(it->Collides(cRect(x0,x1,y0,y1)))
		  return true;
  }

  ///Other
  return false;
}
