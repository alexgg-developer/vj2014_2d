#include "cPlayer.hpp"
#include "cState.hpp"
#include "cExplosion.hpp"
#include "cCoordChanges.hpp"

cPlayer::cPlayer(cScene const& map, cCoordChanges const& ch) : cBicho(map, ch) {
  mStates[STATE_LOOKLEFT ]->getAni().setNumberOfFrames(4);
  mStates[STATE_LOOKRIGHT]->getAni().setNumberOfFrames(4);
  mStates[STATE_WALKLEFT ]->getAni().setNumberOfFrames(8);
  mStates[STATE_WALKRIGHT]->getAni().setNumberOfFrames(8);
  mStates[STATE_JUMPLEFT ]->getAni().setNumberOfFrames(7);
  mStates[STATE_JUMPRIGHT]->getAni().setNumberOfFrames(6);
  
  static float const wi = 778;
  static float const he = 267;
  mStates[STATE_LOOKLEFT ]->getAni().setInitialFrame(Vec3( 0.0f, 174.0f/he));
  mStates[STATE_LOOKRIGHT]->getAni().setInitialFrame(Vec3( 0.0f,  87.0f/he));
  mStates[STATE_WALKLEFT ]->getAni().setInitialFrame(Vec3(245.0f/wi, 174.0f/he));
  mStates[STATE_WALKRIGHT]->getAni().setInitialFrame(Vec3(245.0f/wi,  87.0f/he));
  mStates[STATE_JUMPLEFT ]->getAni().setInitialFrame(Vec3(400.0f/wi, 270.0f/he));
  mStates[STATE_JUMPRIGHT]->getAni().setInitialFrame(Vec3( 0.0f    , 270.0f/he));

  mStates[STATE_LOOKLEFT ]->getAni().setDeltaFrame(Vec3(50.0f / wi, 0.0f));
  mStates[STATE_LOOKRIGHT]->getAni().setDeltaFrame(Vec3(50.0f / wi, 0.0f));
  mStates[STATE_WALKLEFT ]->getAni().setDeltaFrame(Vec3(60.0f / wi, 0.0f));
  mStates[STATE_WALKRIGHT]->getAni().setDeltaFrame(Vec3(60.0f / wi, 0.0f));
  mStates[STATE_JUMPLEFT ]->getAni().setDeltaFrame(Vec3(54.0f / wi, 0.0f));
  mStates[STATE_JUMPRIGHT]->getAni().setDeltaFrame(Vec3(54.0f / wi, 0.0f));

  mStates[STATE_LOOKLEFT ]->getAni().setFrameSize(Vec3(50.0f / wi, -87.0f / he));
  mStates[STATE_LOOKRIGHT]->getAni().setFrameSize(Vec3(50.0f / wi, -87.0f / he));
  mStates[STATE_WALKLEFT ]->getAni().setFrameSize(Vec3(60.0f / wi, -87.0f / he));
  mStates[STATE_WALKRIGHT]->getAni().setFrameSize(Vec3(60.0f / wi, -87.0f / he));
  mStates[STATE_JUMPLEFT ]->getAni().setFrameSize(Vec3(50.0f / wi, -87.0f / he));
  mStates[STATE_JUMPRIGHT]->getAni().setFrameSize(Vec3(50.0f / wi, -87.0f / he));
  
  static float const delay = 1000000;
  mStates[STATE_JUMPLEFT ]->getAni().setFrameDelay(delay*2.0f);
  mStates[STATE_JUMPRIGHT]->getAni().setFrameDelay(delay*2.0f);
  mStates[STATE_WALKLEFT ]->getAni().setFrameDelay(delay);
  mStates[STATE_WALKRIGHT]->getAni().setFrameDelay(delay);
  mStates[STATE_LOOKLEFT ]->getAni().setFrameDelay(delay);
  mStates[STATE_LOOKRIGHT]->getAni().setFrameDelay(delay);
}
cPlayer::~cPlayer(){}

void cPlayer::Draw(float const t, float const dt) const {
  cFrame const fr = mActualState->getFrame(t);

  DrawRect(fr, mCoordChange.WorldToScreen(posW));
  for (std::size_t i = 0; i < mAttacks.size(); ++i) {
	  mAttacks[i].Draw(t,dt);
  }
}
bool cPlayer::Init() {
  return mText.Load("Zoro.png",GL_RGBA); }

 void cPlayer::Attack() {
   cExplosion::addExplosion(mMap, mCoordChange, posW);		
 }
#include <iostream>
 void cPlayer::Attack(Vec3 & direction, cElementalProjectile::KindOfElement element) {
	 cElementalProjectile eProjectile = cElementalProjectile(*this, mMap, mCoordChange, element);
	 if (direction == Vec3(0, 0, 0)) {
		 //std::cout << "Wow that happened" << std::endl;
		 if (mStates[STATE_LOOKLEFT].get() == mActualState || mStates[STATE_JUMPLEFT].get() == mActualState) {
			 direction.x = -1.0f;
		 }
		 else if (mStates[STATE_LOOKRIGHT].get() == mActualState || mStates[STATE_JUMPRIGHT].get() == mActualState) {
			 direction.x = 1.0f;
		 }
	 }
	 eProjectile.changeDirection(direction);
	 eProjectile.SetPosition_W(this->GetPosition_W());
   eProjectile.AffectsProta (false);
   eProjectile.AffectEnemies(true);
	 mAttacks.push_back(eProjectile);
 }

 void cPlayer::doLogic(float const t, float const dt) {
	 Logic();
	 for (std::size_t i = 0; i < mAttacks.size(); ++i) {
		 mAttacks[i].doLogic(t,dt);
	 }
   Vec3 const tilePos = mCoordChange.WorldToTile(posW);
   if(tilePos.y<0) mLife = 0;
 }