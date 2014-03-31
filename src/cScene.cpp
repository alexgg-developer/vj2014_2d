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
#include "cState.hpp"
#include "cGame.hpp"

void cMenu::UpKey() {
  if(!mShowingInstr)
    mActualState->Jump();
  else {
    mShowingInstr = false;
    mActualState = &*mStates[MenuState::INSTRUCTIONS];
  }
}
void cMenu::DownKey() {
  if(!mShowingInstr)
    mActualState->UnJump();
  else {
    mShowingInstr = false;
    mActualState = &*mStates[MenuState::INSTRUCTIONS];
  }
}
void cMenu::UpKeyReal() {
  UpKey();
}
void cMenu::DownKeyReal() {
  DownKey();
}
void cMenu::LeftKey() { mShowingInstr = false; }
void cMenu::RightKey() { mShowingInstr = false; }
void cMenu::doLogic(float const t, float const dt) { }
void cMenu::Draw(float const t, float const dt) const {
  if(!mShowingInstr) {
    bool const EnterSelected = (mActualState==&*mStates[MenuState::ENTER]);
    bool const Lev0Selected = (mActualState==&*mStates[MenuState::LEVEL0]);
    bool const Lev1Selected = (mActualState==&*mStates[MenuState::LEVEL1]);
    bool const ExitSelected = (mActualState==&*mStates[MenuState::EXIT  ]);
    bool const InstrSelected = (mActualState==&*mStates[MenuState::INSTRUCTIONS]);
  
    Vec3 const delta(150, -75);
    Vec3 const next(0.0, delta.y*1.25);


    Vec3 const enterScreen(200, 450);
    mTextures[ENTER*2+EnterSelected].Draw(Vec3(0,0), Vec3(1,1), enterScreen, enterScreen+delta);

    Vec3 const lev0 = enterScreen+next;
    mTextures[LEVEL0*2+Lev0Selected].Draw(Vec3(0,0), Vec3(1,1), lev0, lev0+delta);

    Vec3 const lev1 = lev0+next;
    mTextures[LEVEL1*2+Lev1Selected].Draw(Vec3(0,0), Vec3(1,1), lev1, lev1+delta);
  
    Vec3 const cred = lev1+next;
    mTextures[INSTRUCTIONS*2+InstrSelected].Draw(Vec3(0,0), Vec3(1,1), cred, cred+delta);

    Vec3 const exit = cred+next;
    mTextures[EXIT*2+ExitSelected].Draw(Vec3(0,0), Vec3(1,1), exit, exit+delta);
  
    Vec3 const cred2(exit.x+delta.x*1.1f, exit.y);
    mTextures[10].Draw(Vec3(0,0), Vec3(1,1), cred2, cred2+delta);
  } else {
    Vec3 const enterScreen(50, 500);
    Vec3 const delta(500, -400);
    mTextures[11].Draw(Vec3(0,0), Vec3(1,1), enterScreen, enterScreen+delta);
  }
}
bool cMenu::Init() {
  // Load states
  mStates[ENTER ] = std::make_shared<cState>(this);
  mStates[LEVEL0] = std::make_shared<cState>(this);
  mStates[LEVEL1] = std::make_shared<cState>(this);
  mStates[INSTRUCTIONS] = std::make_shared<cState>(this);
  mStates[EXIT  ] = std::make_shared<cState>(this);

  mStates[ENTER ]->setNextOnJump(mStates[EXIT  ].get());
  mStates[LEVEL0]->setNextOnJump(mStates[ENTER ].get());
  mStates[LEVEL1]->setNextOnJump(mStates[LEVEL0].get());
  mStates[INSTRUCTIONS]->setNextOnJump(mStates[LEVEL1].get());
  mStates[EXIT  ]->setNextOnJump(mStates[INSTRUCTIONS].get());

  mStates[ENTER ]->setNextOnUnJump(mStates[LEVEL0].get());
  mStates[LEVEL0]->setNextOnUnJump(mStates[LEVEL1].get());
  mStates[LEVEL1]->setNextOnUnJump(mStates[INSTRUCTIONS].get());
  mStates[INSTRUCTIONS]->setNextOnUnJump(mStates[EXIT ].get());
  mStates[EXIT  ]->setNextOnUnJump(mStates[ENTER ].get());

  mActualState = mStates[ENTER].get();

  // Load textures
  mTextures[ENTER*2].Load("StartGame.png");
  mTextures[ENTER*2+1].Load("StartGameSelected.png");
  mTextures[LEVEL0*2].Load("Level0.png");
  mTextures[LEVEL0*2+1].Load("Level0Selected.png");
  mTextures[LEVEL1*2].Load("Level1.png");
  mTextures[LEVEL1*2+1].Load("Level1Selected.png");
  mTextures[INSTRUCTIONS*2].Load("InstrMenu.png");
  mTextures[INSTRUCTIONS*2+1].Load("InstrMenuSelected.png");
  mTextures[EXIT*2].Load("Exit.png");
  mTextures[EXIT*2+1].Load("ExitSelected.png");
  mTextures[10].Load("Creditos.png");
  mTextures[11].Load("instruccions.png");
  return true;
}
bool cMenu::LoadLevel(int level) {
//??
  return true;
}
void cMenu::PressedEnter() {
  if (mShowingInstr) mShowingInstr = false;
  else {
    if(mActualState==&*mStates[MenuState::ENTER] || mActualState==&*mStates[MenuState::LEVEL0]) {
      cScene* cs = new cScene(mGame,1);
      cs->Init();
      cs->LoadLevel(0);
      mGame->changeLevel(cs);
    } else if(mActualState==&*mStates[MenuState::LEVEL1]) {
      cScene* cs = new cScene(mGame,2);
      cs->Init();
      cs->LoadLevel(1);
      mGame->changeLevel(cs);
    } else if(mActualState==&*mStates[MenuState::INSTRUCTIONS]) {
      mShowingInstr = true;
    } else if(mActualState==&*mStates[MenuState::EXIT]) {
      exit(0);//TODO: Delete everything correctly
    } else {
      std::cout << "WTF?!?!?!" << std::endl;
      exit(0);
    }
  }
}


cScene::cScene(cGame* aGame, int const nextLev) : iScene(aGame), CoordChanges(), Player(*this, CoordChanges),
 mExitDoor(*this, CoordChanges, Player, aGame, nextLev),
 mInterruptor(*this, CoordChanges, Player, mExitDoor),
 mHud(*this, CoordChanges) {
   //mBackup=*this;
 }

cScene::~cScene() {}

bool cScene::Init() {
	//Player initialization
	Player.Init();
	Player.SetWidthHeight_W(40,40);
	Player.SetPosition_T(Vec3(2,1)); //Initial tile
	Player.mLife = 3;

	mHud.Init();
	mHud.SetWidthHeight_W(32, 32);
	mHud.SetPosition_T(Vec3(0, 26));
  mExitDoor.Init();
  mExitDoor.SetWidthHeight_W(32,64);
  mInterruptor.Init();
  mInterruptor.SetWidthHeight_W(32,32);
	
  cExplosion::initialize(this);

  return mText.Load("blocks.png",GL_RGBA);
}
bool cScene::LoadLevel(int level) {
  mLevel = level;
  // get filename
  std::stringstream stream, stream2;
  stream << "level";
  if(level<10) stream << "0";
  stream << level << ".txt";
  std::string file = stream.str();

  stream2 << "Depth" << level << ".png";
  mFondo.Load(stream2.str().c_str());
  mForeground.Load("Foreground.png");
  
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

  //Enemies
  unsigned int walkingBombs;
  fd >> walkingBombs;
  for(unsigned int i=0; i<walkingBombs; ++i) {
    int life;
    int posX, posY;
    fd >> life >> posX >> posY;
    mEnemies.push_back(new cWalkingBomb(*this, CoordChanges, life, Vec3(posX, posY), true, Player));
  }

  unsigned int normalShips;
  fd >> normalShips;
  for(unsigned int i=0; i<normalShips; ++i) {
    int life;
    int posX, posY;
    fd >> life >> posX >> posY;
    mEnemies.push_back(new cNormalShip(Player, *this, CoordChanges, life, Vec3(posX, posY), true));
  }
  
  fd.close();

  return true;
}

void cScene::DrawScreen(float const t, float const dt) const {
  mHud.Draw(t, dt);
  Vec3 const enterScreen(0, 480);
  Vec3 const delta(640, -480);
  Vec3 const enterScreenFondo(enterScreen.x, enterScreen.y, -10);
  Vec3 const enterScreenForeground(enterScreen.x, enterScreen.y, 10);
  mForeground.Draw(Vec3(0,0), Vec3(1,1), enterScreenForeground, enterScreenForeground+delta);
}
void cScene::DrawScreenPre(float const t, float const dt) const {
  mHud.Draw(t, dt);
  Vec3 const enterScreen(0, 480);
  Vec3 const delta(640, -480);
  Vec3 const enterScreenFondo(enterScreen.x, enterScreen.y, -10);
  Vec3 const enterScreenForeground(enterScreen.x, enterScreen.y, 10);
  mFondo.Draw(Vec3(0,0), Vec3(1,1), enterScreenFondo, enterScreenFondo+delta);
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
//cScene cScene::mBackup(nullptr,0);
void cScene::doLogic(float const t, float const dt) {
	Player.doLogic(t,dt);
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
  mHud.update(Player.mLife);
  mCamPosition = std::fmax(0.0f, Player.GetPosition_W().x - GAME_WIDTH / 2.0f);

  if(Player.mLife<=0) {
    //Resetea el mismo nivel.
    iScene* sc = new cMenu(mGame);
    sc->Init();
    mGame->changeLevel(sc);
    /*Player.reset();
    mExitDoor.reset();
    mInterruptor.reset();
    LoadLevel(mLevel);*/
  } else {
    //Exit door may delete the scene, it's convenient to have it as the last one to update ;-)
    mExitDoor.doLogic(t,dt);
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
