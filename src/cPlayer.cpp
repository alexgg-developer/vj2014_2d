#include "cPlayer.hpp"
#include "cState.hpp"
#include "cExplosion.hpp"

cPlayer::cPlayer(cScene const& map, cCoordChanges const& ch) : cBicho(map, ch) {
  mStates[STATE_LOOKLEFT ]->getAni().setNumberOfFrames(4);
  mStates[STATE_LOOKRIGHT]->getAni().setNumberOfFrames(4);
  mStates[STATE_WALKLEFT ]->getAni().setNumberOfFrames(8);
  mStates[STATE_WALKRIGHT]->getAni().setNumberOfFrames(8);
  mStates[STATE_JUMPLEFT ]->getAni().setNumberOfFrames(7);
  mStates[STATE_JUMPRIGHT]->getAni().setNumberOfFrames(6);

  mStates[STATE_LOOKLEFT ]->getAni().setInitialFrame(Vec3(0.0f, 174.0f/300.0f));
  mStates[STATE_LOOKRIGHT]->getAni().setInitialFrame(Vec3(0.0f, 87.0f / 300.0f));
  mStates[STATE_WALKLEFT ]->getAni().setInitialFrame(Vec3(245.0f / 740.0f, 174.0f / 300.0f));
  mStates[STATE_WALKRIGHT]->getAni().setInitialFrame(Vec3(245.0f / 740.0f, 87.0f / 300.0f));
  mStates[STATE_JUMPLEFT ]->getAni().setInitialFrame(Vec3(400.0f/740.0f, 270.0f/300.0f));
  mStates[STATE_JUMPRIGHT]->getAni().setInitialFrame(Vec3(0.0f, 270.0f / 300.0f));

  mStates[STATE_LOOKLEFT ]->getAni().setDeltaFrame(Vec3(50.0f / 740.0f, 0.0f));
  mStates[STATE_LOOKRIGHT]->getAni().setDeltaFrame(Vec3(50.0f / 740.0f, 0.0f));
  mStates[STATE_WALKLEFT ]->getAni().setDeltaFrame(Vec3(60.0f / 740.0f, 0.0f));
  mStates[STATE_WALKRIGHT]->getAni().setDeltaFrame(Vec3(60.0f / 740.0f, 0.0f));
  mStates[STATE_JUMPLEFT ]->getAni().setDeltaFrame(Vec3(55.0f / 740.0f, 0.0f));
  mStates[STATE_JUMPRIGHT]->getAni().setDeltaFrame(Vec3(55.0f / 740.0f, 0.0f));

  mStates[STATE_LOOKLEFT ]->getAni().setFrameSize(Vec3(50.0f / 740.0f, -87.0f / 300.0f));
  mStates[STATE_LOOKRIGHT]->getAni().setFrameSize(Vec3(50.0f / 740.0f, -87.0f / 300.0f));
  mStates[STATE_WALKLEFT ]->getAni().setFrameSize(Vec3(60.0f / 740.0f, -87.0f / 300.0f));
  mStates[STATE_WALKRIGHT]->getAni().setFrameSize(Vec3(60.0f / 740.0f, -87.0f / 300.0f));
  mStates[STATE_JUMPLEFT ]->getAni().setFrameSize(Vec3(55.0f / 740.0f, -87.0f / 300.0f));
  mStates[STATE_JUMPRIGHT]->getAni().setFrameSize(Vec3(50.0f / 740.0f, -87.0f / 300.0f));
  
  mStates[STATE_JUMPLEFT ]->getAni().setFrameDelay(9);
  mStates[STATE_JUMPRIGHT]->getAni().setFrameDelay(10);
}
cPlayer::~cPlayer(){}

void cPlayer::Draw() {
  cFrame const fr = mActualState->getAni().Generate();
  mActualState->getAni().NextFrame();

  DrawRect(fr, mCoordChange.WorldToScreen(posW));
  for (auto i = 0; i < mAttacks.size(); ++i) {
	  mAttacks[i].draw();
  }
}
bool cPlayer::Init() {
  return mText.Load("Zoro.png",GL_RGBA); }

 void cPlayer::Attack() {
   cExplosion::addExplosion(mMap, mCoordChange, posW);		
 }

 void cPlayer::Attack(Vec3 const & direction, cElementalProjectile::KindOfElement element) {
	 cElementalProjectile eProjectile = cElementalProjectile(mCoordChange, element);
	 eProjectile.mPhysics->changeDirection(direction);
	 eProjectile.mWPosition = this->GetPosition_W();
	 eProjectile.mAwake = true;
	 mAttacks.push_back(eProjectile);
 }

 void cPlayer::doLogic(float dt)
 {
	 Logic();
	 for (auto i = 0; i < mAttacks.size(); ++i) {
		 mAttacks[i].doLogic(dt);
	 }
 }