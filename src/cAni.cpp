#include "cAni.hpp"

cAni::cAni() : seq(0), delay(0), mTex0(0, 0), mTexIncrement(0, 1), mMax(1), mFrameSize(0.25, -0.25), mFrameDelay(8) {}


cFrame cAni::Generate() const {
  Vec3 const tex0 = mTex0 + mTexIncrement*seq;
  Vec3 const texf = tex0 + mFrameSize;
  return cFrame(tex0, texf);
}
void cAni::setDeltaFrame(Vec3 const& av) {
  mTexIncrement = av; }
void cAni::setInitialFrame(Vec3 const& ini) {
  mTex0 = ini; }

void cAni::NextFrame() {
  delay++;
  if(delay == mFrameDelay) {
    seq++;
    seq%=mMax;//TODO: if mmax==1, does it work as expected?
    delay = 0;
  }
}

int cAni::GetFrame() const {
  return seq; }

void cAni::reset() {
  seq=0;
  delay=0;
}
