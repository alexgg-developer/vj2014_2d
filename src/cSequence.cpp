
#include "cSequence.hpp"
cSequence::cSequence(cTexture const& aText, cAni const& aAni, std::function<void()> aOnEndAni) : mText(aText), mAni(aAni), mOnEndAni(aOnEndAni), mInitT(-1) {}
void cSequence::doLogic(float const dt) {
  if(mAni.isInLastFrame(mInitT+dt)) {
    aOnEndAni();
  }
}
void cSequence::draw(float const dt) const {
  if(mInitT>0) {
    cFrame fr = mAni.generate(mInitT+dt);
    mText.draw(fr);
  }
}
void cSequence::reset() {
  mAni.reset(); }

void cSequence::compose(cSequence& other) {
  mOnEndAni = [&other](){
    other.reset();
  };
}
