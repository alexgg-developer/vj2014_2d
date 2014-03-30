#include "cPuerta.hpp"
#include "cState.hpp"
#include "cExplosion.hpp"
#include "cPlayer.hpp"
#include "cCoordChanges.hpp"

enum States { 
  STATE_CLOSED=0,
  STATE_OPENING=1,
  STATE_OPENED=2, };
cPuerta::cPuerta(cScene const& map, cCoordChanges const& ch, cPlayer& player) : mPlayer(player)
  , cBicho(map, ch), mActive(false) {
  float const p_w = 130;
  float const p_h = 114;
  mStates[STATE_CLOSED ]->getAni().setNumberOfFrames(1); //Closed
  mStates[STATE_OPENING]->getAni().setNumberOfFrames(4); //Opening
  mStates[STATE_OPENED ]->getAni().setNumberOfFrames(1); //Opened

  mStates[STATE_CLOSED ]->getAni().setInitialFrame(Vec3(0.0f, 56.0f/p_h));
  mStates[STATE_CLOSED ]->getAni().setFrameSize(Vec3(32.0f/p_w, -56.0f/p_h));

  mStates[STATE_OPENED ]->getAni().setInitialFrame(Vec3(97.0f/p_w, 1.0f));
  mStates[STATE_OPENED ]->getAni().setFrameSize(Vec3(32.0f/p_w, -56.0f/p_h));

  mStates[STATE_OPENING]->getAni().setInitialFrame(Vec3(0.0f, 56.0f/p_h));
  mStates[STATE_OPENING]->getAni().setFrameSize(Vec3(32.0f/p_w, -56.0f/p_h));
  mStates[STATE_OPENING]->getAni().setDeltaFrame(Vec3(32.0f/p_w, 0.0f));
  mStates[STATE_OPENING]->getAni().setFrameDelay(2300000);

  mStates[STATE_CLOSED ]->setNextOnActivate(&*mStates[STATE_OPENING]);
  mStates[STATE_OPENING]->setNextOnAnimationFinished(&*mStates[STATE_OPENED]);
  
  mStates[STATE_OPENING]->getAni().setRepeat(cAni::AnimationType::SINGLE);
  mStates[STATE_OPENED ]->getAni().setRepeat(cAni::AnimationType::SINGLE);
  mStates[STATE_CLOSED ]->getAni().setRepeat(cAni::AnimationType::SINGLE);
}
cPuerta::~cPuerta(){}

void cPuerta::Draw(float const t, float const dt) const {
  cFrame const fr = mActualState->getFrame(t);
  DrawRect(fr, mCoordChange.WorldToScreen(posW));
}
bool cPuerta::Init() {

  return mText.Load("Door.png",GL_RGBA); }
#include <iostream>
void cPuerta::doLogic(float const t, float const dt) {
  ///Check collision with player
  if(mActive) {
    if(mPlayer.GetBBox().collides(this->GetBBox())) {
      //Exit level -> cSequence
      mActualState->Activate();
      mActive=false;
      std::cout << "You won!" << std::endl;
    }
  }
}
