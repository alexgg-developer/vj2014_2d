#include "cBicho.hpp"
#include "cScene.hpp"
#include "Globals.hpp"
#include "cState.hpp"

#define STEP_LENGTH		4
#define JUMP_HEIGHT		96
#define JUMP_STEP		4

cBicho::cBicho(cScene const& map, cCoordChanges const& ch) : mMap(map), mCoordChange(ch), jumping(false), w(10), h(10) {
  initStates();
}
cBicho::~cBicho(void){}

cBicho::cBicho(cScene const& map, cCoordChanges const& ch, int posxW,int posyW,int width,int height) : mMap(map), mCoordChange(ch) {
  posW.x = posxW;
  posW.y = posyW;
  w = width;
  h = height;
  initStates();
}
void cBicho::initStates() {
  mStates[STATE_LOOKLEFT ] = std::make_shared<cState>(*this);
  mStates[STATE_LOOKRIGHT] = std::make_shared<cState>(*this);
  mStates[STATE_WALKLEFT ] = std::make_shared<cState>(*this);
  mStates[STATE_WALKRIGHT] = std::make_shared<cState>(*this);
  mStates[STATE_JUMPLEFT ] = std::make_shared<cState>(*this);
  mStates[STATE_JUMPRIGHT] = std::make_shared<cState>(*this);

  mStates[STATE_WALKLEFT]->setNextOnStop(mStates[STATE_LOOKLEFT].get());
  mStates[STATE_WALKRIGHT]->setNextOnStop(mStates[STATE_LOOKRIGHT].get());
  
  mStates[STATE_LOOKLEFT]->setNextOnRight(mStates[STATE_LOOKRIGHT].get());
  mStates[STATE_LOOKRIGHT]->setNextOnLeft(mStates[STATE_LOOKLEFT].get());
  mStates[STATE_LOOKLEFT]->setNextOnLeft(mStates[STATE_WALKLEFT].get());
  mStates[STATE_LOOKRIGHT]->setNextOnRight(mStates[STATE_WALKRIGHT].get());
  mStates[STATE_WALKLEFT]->setNextOnRight(mStates[STATE_WALKRIGHT].get());
  mStates[STATE_WALKRIGHT]->setNextOnLeft(mStates[STATE_WALKLEFT].get());
  mStates[STATE_JUMPLEFT]->setNextOnRight(mStates[STATE_JUMPRIGHT].get());
  mStates[STATE_JUMPRIGHT]->setNextOnLeft(mStates[STATE_JUMPLEFT].get());
  
  mStates[STATE_LOOKLEFT]->setNextOnJump(mStates[STATE_JUMPLEFT].get());
  mStates[STATE_LOOKRIGHT]->setNextOnJump(mStates[STATE_JUMPRIGHT].get());
  mStates[STATE_WALKLEFT]->setNextOnJump(mStates[STATE_JUMPLEFT].get());
  mStates[STATE_WALKRIGHT]->setNextOnJump(mStates[STATE_JUMPRIGHT].get());
  mStates[STATE_LOOKLEFT]->setNextOnJump(mStates[STATE_JUMPLEFT].get());
  mStates[STATE_LOOKRIGHT]->setNextOnJump(mStates[STATE_JUMPRIGHT].get());
  
  mStates[STATE_JUMPLEFT]->setNextOnUnJump(mStates[STATE_LOOKLEFT].get());
  mStates[STATE_JUMPRIGHT]->setNextOnUnJump(mStates[STATE_LOOKRIGHT].get());

  mActualState = mStates[STATE_LOOKLEFT].get();
}
void cBicho::SetPosition_W(Vec3 apos) {
  posW = apos;
}

Vec3 cBicho::GetPosition_W() const {
  return posW; }
void cBicho::SetPosition_T(Vec3 tile) {
  posW = mCoordChange.TileToWorld(tile);
}

Vec3 cBicho::GetPosition_T() const {
  return mCoordChange.WorldToTile(posW); }
void cBicho::SetWidthHeight_W(int width,int height) {
  w = width;
  h = height; }

int cBicho::GetWidth_W() const { return w;}
int cBicho::GetHeight_W() const{ return h;}
bool cBicho::CollidesMapWall(bool right) const {
  Vec3 posW2 = posW;

  if(right) posW2.x += w;
	
  return mMap.CollisionInClosedArea(cRect(posW2.x, posW2.x, posW2.y, posW2.y+h-1));
}

bool cBicho::CollidesMapFloor() const {
  return mMap.CollisionInClosedArea(cRect(posW.x, posW.x+w-1, posW.y-1, posW.y-1));
}

cRect cBicho::GetArea_W() const {
  return cRect(posW.x, posW.x+w, posW.y, posW.y+h);
}
void cBicho::DrawRect(cFrame const& fr,
		      Vec3 const& screen) const {
  mText.Draw(fr, screen, Vec3(screen.x+w, screen.y+h));
}

void cBicho::MoveLeft() {
  if (!CollidesMapWall(false)) {
    posW.x -= STEP_LENGTH;
    mActualState->Left();
    AdjustOverLeft();
  }
}
void cBicho::MoveRight() {
  if (!CollidesMapWall(true)) {
    posW.x  += STEP_LENGTH;
    mActualState->Right();
    AdjustOverRight();
  }
}

void cBicho::Stop() {
  mActualState->Stop();
}
void cBicho::Jump() {
  if(!jumping) {
    if(CollidesMapFloor()) {
      jumping = true;
      mActualState->Jump();
      jump_alfa = 0;
      jump_y = posW.y;
    }
  } else mActualState->Stop();
}
#include <iostream>
void cBicho::AdjustOverEarth() { 
  AdjustOverVec(Vec3(0, 1), [&]() { return this->CollidesMapFloor(); }); }
void cBicho::AdjustOverLeft() { 
  AdjustOverVec(Vec3( 1,0), [&]() { return this->CollidesMapWall(false)
   || this->mMap.CollisionInClosedArea(cRect(posW.x, posW.x+w-1, posW.y, posW.y  )); }); }
void cBicho::AdjustOverRight() { 
  AdjustOverVec(Vec3(-1,0), [&]() { return this->CollidesMapWall(true)
   || this->mMap.CollisionInClosedArea(cRect(posW.x, posW.x+w-1, posW.y, posW.y  )); }); }
void cBicho::AdjustOverVec(Vec3 const& v, std::function<bool()> const& cond) {
  int executed_times = 0;
  while(cond()) {
	  posW += v;
    executed_times++;
	}
  if(executed_times>0) {
    posW += -v;
    if(executed_times>1)
      mActualState->Stop();
  }
}
void cBicho::Logic() {
  if(jumping)	{
    jump_alfa += JUMP_STEP;
		
    if(jump_alfa >= 180) {
      jumping = false;
      mActualState->UnJump();
      posW.y = jump_y;
    }
    else {
      /// I really love magic constants. I love them until I puke.
      float alfa = ((float)jump_alfa) * 0.017453f;
      float oldy = posW.y;
      posW.y = jump_y + ( float(JUMP_HEIGHT) * sin(alfa) );
		
      if(jump_alfa > 90) {
	      //Over floor?
	      jumping = !CollidesMapFloor();
	      // Col�calo en el suelo, motherfucker
	      if(!jumping) {
          mActualState->UnJump();
          AdjustOverEarth();
	      }
      }
    }
  }
  else {
    //Ca�da libre muy cutre
    if(!CollidesMapFloor()) {
      mActualState->Jump();
      posW.y -= (STEP_LENGTH);
      AdjustOverEarth();
    } else mActualState->UnJump();
    
  }
}
cState* cBicho::GetState() const {
  return mActualState; }
void cBicho::SetState(cState* s) {
  mActualState = s;
  mActualState->reset();
}
