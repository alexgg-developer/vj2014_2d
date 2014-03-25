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
  void setFrameSize(Vec3 const& fs) { mFrameSize = fs;  }
  void setFrameDelay(unsigned int const del) { mFrameDelay = del; }

  bool isInLastFrame() const { return seq==(mMax-1); }
protected:
  int seq,delay;
  unsigned int mFrameDelay;
  Vec3 mTex0;
  Vec3 mTexIncrement;
  Vec3 mFrameSize;
  unsigned int mMax;
  //  Vec3
};
