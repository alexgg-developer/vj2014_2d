#include "cPlayer.hpp"
#include "cState.hpp"

cPlayer::cPlayer(cScene const& map, cCoordChanges const& ch) : cBicho(map, ch) {
  mStates[STATE_LOOKLEFT ]->getAni().setNumberOfFrames(1);
  mStates[STATE_LOOKRIGHT]->getAni().setNumberOfFrames(1);
  mStates[STATE_WALKLEFT ]->getAni().setNumberOfFrames(3);
  mStates[STATE_WALKRIGHT]->getAni().setNumberOfFrames(3);

  mStates[STATE_LOOKLEFT ]->getAni().setInitialFrame(Vec3(0.0f , 0.25f));
  mStates[STATE_LOOKRIGHT]->getAni().setInitialFrame(Vec3(0.25f, 0.25f));
  mStates[STATE_WALKLEFT ]->getAni().setInitialFrame(Vec3(0.0f , 0.25f));
  mStates[STATE_WALKRIGHT]->getAni().setInitialFrame(Vec3(0.25f, 0.25f));

  mStates[STATE_WALKLEFT ]->getAni().setDeltaFrame(Vec3(0.0f, 0.25f));
  mStates[STATE_WALKRIGHT]->getAni().setDeltaFrame(Vec3(0.0f, 0.25f));
}
cPlayer::~cPlayer(){}

void cPlayer::Draw() {
  cFrame const fr = mActualState->getAni().Generate();
  mActualState->getAni().NextFrame();

  DrawRect(fr, mCoordChange.WorldToScreen(posW));
}
bool cPlayer::Init() {
  return mText.Load("bub.png",GL_RGBA); }
