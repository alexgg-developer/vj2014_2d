#include "cAni.hpp"
#undef min
#include <algorithm>
#include <assert.h>
#include <iostream>

cAni::cAni() : mDelayBetweenFrames(1000000), mTex0(0, 0), mTexIncrement(0, 1), mNumberOfFrames(1),
 mFrameSize(0.25, -0.25), mInitT(-1) {}


cFrame cAni::Generate(float const t) const {
  Vec3 const tex0 = mTex0 + mTexIncrement*GetFrame(t);
  Vec3 const texf = tex0 + mFrameSize;
  return cFrame(tex0, texf);
}
void cAni::setDeltaFrame(Vec3 const& av) {
  mTexIncrement = av; }
void cAni::setInitialFrame(Vec3 const& ini) {
  mTex0 = ini; }

int cAni::GetFrame(float const t) const {
  if(mInitT<0) return 0;//TODO: Detet error
  float dt = (t-mInitT);
  float const duration = getDuration();
  switch(mRepeat) {
    case REPEAT: {
      while(dt>duration) {
        mInitT+=duration;
        dt = (t-mInitT);
      }
      break;
    }
    case PING_PONG_NORMAL: {
      if(dt>duration) {
        mInitT+=2.0*duration; //Advance it!
        mRepeat=PING_PONG_REVERSED;
        std::cout << "Change to reversed" << std::endl;
      }
      break;
    }
    case PING_PONG_REVERSED: {
      if(dt>0) {
        mRepeat=PING_PONG_NORMAL;
        std::cout << "Change to normal" << std::endl;
      }
    }
    case SINGLE: {
      break;
    }
  }
  dt = (t-mInitT); //recalc
  if(dt<0) {
    if(mRepeat==PING_PONG_REVERSED)
      dt = std::abs(dt);//dt<0
    else dt=0;
  }
  float const calFrame = dt/mDelayBetweenFrames;
  return std::min<int>(mNumberOfFrames, calFrame); }
  
float cAni::getDuration() const {
  return mDelayBetweenFrames*float(mNumberOfFrames); }
void cAni::reset(float const t) {
  mInitT = t;
  if(mRepeat==PING_PONG_REVERSED)
    mRepeat=PING_PONG_NORMAL;
}
