#include "cSequence.hpp"
#include "Timer.hpp"
#undef max
#undef min
#include <algorithm>

cSequence::cSequence(Vec3 const& aScreenPos0, Vec3 const& aScreenPos1, cTexture const& aText, cAni const& aAni, std::function<void()> aOnEndAni)
 : mText(aText), mAni(aAni), mOnEndAni(aOnEndAni), mInitT(-1), mScreenPos0(aScreenPos0), mScreenPos1(aScreenPos1) {}
void cSequence::doLogic(float const dt) {
  if(mAni.isInLastFrame(mInitT+dt)) {
    mOnEndAni();
  }
}
void cSequence::draw(float const dt) const {
  if(mInitT>0) {
    cFrame fr = mAni.Generate(mInitT+dt);
    mText.Draw(fr, mScreenPos0, mScreenPos1);
  }
}
void cSequence::reset(float const t) {
  mAni.reset(t); }


void cSequence_Composed::addNextSeq(cSequence const& seq) {
  mSequences.push_back(seq);
  mSequences.back().setOnEndAni([this](){ this->jumpToNextSeq(this->mSequences.size()-2); });
}
void cSequence_Composed::jumpToNextSeq(int next) {
  mActiveSequence=std::max(0,next);
  reset(Timer::getTNow());
}
void cSequence_Composed::doLogic(float const dt) { mSequences[mActiveSequence].doLogic(dt); }
void cSequence_Composed::draw(float const dt) const { mSequences[mActiveSequence].draw(dt); }
void cSequence_Composed::reset(float const t) { mSequences[mActiveSequence].reset(t); }