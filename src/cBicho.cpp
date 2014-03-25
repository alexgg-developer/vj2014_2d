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
bool cBicho::Collides_W(cRect const& rcW) const {
  return !((posW.x > rcW.right) || (rcW.left > (posW.x+w)) || (posW.y > rcW.top) || (rcW.bottom > (posW.y+h)));
}
bool cBicho::CollidesMapWall(bool right) const {
  Vec3 posW2 = posW;
  int const w2  = w;

  if(right) posW2.x += w2;
	
  bool collides = mMap.CollisionInClosedArea(posW2, Vec3(posW2.x, posW2.y+h-1));
  return collides;
}

bool cBicho::CollidesMapFloor() const {
  int w2 = w;
  if( (int(posW.x) % mCoordChange.GetTileSize()) != 0) w2++;

  bool on_base = false;
  if( (int(posW.y) % mCoordChange.GetTileSize()) == 0 )
    on_base = mMap.CollisionInClosedArea(Vec3(posW.x, posW.y-1), Vec3(posW.x+w2-1, posW.y-1));
  else {
    on_base = mMap.CollisionInClosedArea(Vec3(posW.x, posW.y  ), Vec3(posW.x+w2-1, posW.y  ));
  }

  return on_base;
}

cRect cBicho::GetArea_W() const {
  return cRect(posW.x, posW.x+w, posW.y, posW.y+h);
}
void cBicho::DrawRect(cFrame const& fr,
		      Vec3 const& screen) const {
  mText.Draw(fr, screen, Vec3(screen.x+w, screen.y+h));
}

void cBicho::MoveLeft() {
  //Whats next tile?
  if( (int(posW.x) % mCoordChange.GetTileSize()) == 0) {
    int xaux = posW.x;
    posW.x -= STEP_LENGTH;

    if(CollidesMapWall(false)) {
      posW.x = xaux;
      mActualState->Stop();
    }
  }
  //Advance, no problem
  else {
    posW.x -= STEP_LENGTH;
    mActualState->Left();
  }
}
void cBicho::MoveRight() {
  //Whats next tile?
  if( (int(posW.x) % mCoordChange.GetTileSize()) == 0) {
    int xaux;
    xaux = posW.x;
    posW.x += STEP_LENGTH;

    if(CollidesMapWall(true)) {
      posW.x = xaux;
      mActualState->Stop();
    }
  }
  //Advance, no problem
  else {
    posW.x += STEP_LENGTH;
    mActualState->Right();
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
void cBicho::Logic() {
  if(jumping)	{
    jump_alfa += JUMP_STEP;
		
    if(jump_alfa == 180) {
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
	      // Colócalo en el suelo, motherfucker
	      if(!jumping) {
          mActualState->UnJump();
	        int const w2 = w;
	        //if( (int(posW.x) % mCoordChange.GetTileSize()) != 0) w2++;//No sé que hace. Estaba en el código original.
	        while(mMap.CollisionInClosedArea(Vec3(posW.x, posW.y  ), Vec3(posW.x+w2-1, posW.y  ))) {
	          posW.y +=1;
	        }
	      }
      }
    }
  }
  else {
    //Caída libre muy cutre
    if(!CollidesMapFloor()) {
      mActualState->Jump();
      posW.y -= (STEP_LENGTH);
    } else mActualState->UnJump();
  }
}
cState* cBicho::GetState() const {
  return mActualState; }
void cBicho::SetState(cState* s) {
  mActualState = s;
  mActualState->reset();
}
