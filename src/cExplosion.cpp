#include "cExplosion.hpp"
#include "cGame.hpp"
#include "Timer.hpp"

cExplosion::cExplosion(cScene const& map, cCoordChanges const& ch) : mAnimation(), cBicho(map, ch) {
  mText.Load("Explosion.png", GL_RGBA);

  mAnimation.setInitialFrame(Vec3( 360/1000.0 , 310.0/840.0));
  mAnimation.setFrameSize   (Vec3(60.0/1000.0,-160.0/840.0));
  mAnimation.setDeltaFrame  (Vec3(60.0/1000.0, 0.0));
  mAnimation.setNumberOfFrames(8);
  //mAnimation.setFrameDelay(5.0/30.0);
  mAnimation.setRepeat(cAni::AnimationType::SINGLE);
  mAnimation.reset(Timer::getTNow());
}
void cExplosion::start(float const t) {
  mAnimation.reset(t); }
bool cExplosion::hasFinished(float const t) const {
  return mAnimation.isInLastFrame(t); }

void cExplosion::Draw(float const t, float const dt) const {
  cFrame const fr = mAnimation.Generate(t);
  DrawRect(fr, mCoordChange.WorldToScreen(posW));
}
void cExplosion::addExplosion(cScene const& map, cCoordChanges const& ch, Vec3 const& posW) {
  cExplosion expl(map, ch);
  expl.SetPosition_W(posW);
  expl.SetWidthHeight_W(24,48);
  mScene->addExplosion(expl);
}
 cScene* cExplosion::mScene = nullptr;
