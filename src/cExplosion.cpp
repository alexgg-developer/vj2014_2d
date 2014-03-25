#include "cExplosion.hpp"
#include "cGame.hpp"

cExplosion::cExplosion(cScene const& map, cCoordChanges const& ch) : mAnimation(), cBicho(map, ch) {
  mAnimation.setInitialFrame(Vec3( 360/1000.0 , 310.0/840.0));
  mAnimation.setFrameSize   (Vec3(60.0/1000.0,-160.0/840.0));
  mAnimation.setDeltaFrame  (Vec3(60.0/1000.0, 0.0));
  mAnimation.setNumberOfFrames(8);
  mAnimation.setFrameDelay(5);

  mText.Load("Explosion.png", GL_RGBA);
}
void cExplosion::start() {
  mAnimation.reset(); }
bool cExplosion::hasFinished() const {
  return mAnimation.isInLastFrame(); }

void cExplosion::Draw() {
  cFrame const fr = mAnimation.Generate();
  mAnimation.NextFrame();
  DrawRect(fr, mCoordChange.WorldToScreen(posW));
}
void cExplosion::addExplosion(cScene const& map, cCoordChanges const& ch, Vec3 const& posW) {
  cExplosion expl(map, ch);
  expl.SetPosition_W(posW);
  expl.SetWidthHeight_W(24,48);
  mGame->addExplosion(expl);
}
 cGame* cExplosion::mGame = nullptr;
