#pragma once
#include "cFrame.hpp"

struct cAni {
  cAni();
  void reset();
  //cFrame Generate(float time) const;//In near future, I swear.
  cFrame Generate() const;

  void NextFrame();
  int  GetFrame() const;
  void setDeltaFrame(Vec3 const& av);
  void setInitialFrame(Vec3 const& ini);
  void setNumberOfFrames(unsigned int const aMax) { mMax = aMax; }
protected:
  int seq,delay;
  Vec3 mTex0;
  Vec3 mTexIncrement;
  unsigned int mMax;
  //  Vec3
};
