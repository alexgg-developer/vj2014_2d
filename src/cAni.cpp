#include "cAni.hpp"
#undef min
#include <algorithm>

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
  while(mRepeat && dt>duration) {
    mInitT+=duration;
    dt = (t-mInitT);
  }
  float const calFrame = dt/mDelayBetweenFrames;
  return std::min<int>(mNumberOfFrames, calFrame); }
  
float cAni::getDuration() const {
  return mDelayBetweenFrames*float(mNumberOfFrames); }
void cAni::reset(float const t) {
  mInitT = t;
}
