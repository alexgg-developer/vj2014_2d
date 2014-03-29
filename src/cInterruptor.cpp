#include "cInterruptor.hpp"
#include "cState.hpp"
#include "cExplosion.hpp"
#include "cPlayer.hpp"

enum States { 
  STATE_CLOSED=0,
  STATE_OPENING=1,
  STATE_OPENED=2, };
cInterruptor::cInterruptor(cScene const& map, cCoordChanges const& ch, cPlayer& pl, cPuerta & pu)
  : cBicho(map, ch), mActive(true), mPuerta(pu), mPlayer(pl) {
  float const p_w = 130;
  float const p_h = 21;
  mStates[STATE_CLOSED ]->getAni().setNumberOfFrames(1); //Closed
  mStates[STATE_OPENING]->getAni().setNumberOfFrames(5); //Opening
  mStates[STATE_OPENED ]->getAni().setNumberOfFrames(1); //Opened

  mStates[STATE_CLOSED ]->getAni().setInitialFrame(Vec3(0.0f, 0.0f/p_h));
  mStates[STATE_CLOSED ]->getAni().setFrameSize(Vec3(34.0f/p_w, 56.0f/p_h));

  mStates[STATE_OPENED ]->getAni().setInitialFrame(Vec3(26.0f/p_w, 0.0f/p_h));
  mStates[STATE_OPENED ]->getAni().setFrameSize(Vec3(26.0f/p_w, p_h/p_h));

  mStates[STATE_OPENING]->getAni().setInitialFrame(Vec3(0.0f, 0.0f/p_h));
  mStates[STATE_OPENING]->getAni().setFrameSize(Vec3(26.0f/p_w, p_h/p_h));
  mStates[STATE_OPENING]->getAni().setDeltaFrame(Vec3(26.0f/p_w, p_h/p_h));
  mStates[STATE_OPENING]->getAni().setFrameDelay(9);
}
cInterruptor::~cInterruptor(){}

void cInterruptor::Draw(float const t, float const dt) const {
  cFrame const fr = mActualState->getAni().Generate(t);

  DrawRect(fr, mCoordChange.WorldToScreen(posW));
}
bool cInterruptor::Init() {
  return mText.Load("Switch.png",GL_RGBA); }

  #include <iostream>
void cInterruptor::doLogic(float const t, float const dt) {
  ///Check collision with player
  if(mActive) {
    if(mPlayer.GetBBox().collides(this->GetBBox())) {
      mPuerta.activate();
      mActive=false;
      std::cout << "switch activated!" << std::endl;
    }
  }
}
