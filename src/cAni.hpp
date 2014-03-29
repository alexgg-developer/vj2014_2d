#pragma once
#include "cFrame.hpp"

struct cAni {
  cAni();
  void reset(float const t);
  cFrame Generate(float const t) const;

  int  GetFrame(float const t) const;
  void setDeltaFrame(Vec3 const& av);
  void setInitialFrame(Vec3 const& ini);
  void setNumberOfFrames(unsigned int const aMax) { mNumberOfFrames = aMax; }
  void setFrameSize(Vec3 const& fs) { mFrameSize = fs;  }
  void setFrameDelay(float const del) { mDelayBetweenFrames = del; }
  float getDuration() const;

  bool isInLastFrame(float const t) const { return (mInitT>=0) && (GetFrame(t)>=mNumberOfFrames); }
  void setRepeat(bool const b) { mRepeat = b;}
protected:
  Vec3 mTex0;
  Vec3 mTexIncrement;
  Vec3 mFrameSize;
  int mNumberOfFrames;
  mutable float mInitT;
  float mDelayBetweenFrames;
  bool mRepeat=true;
  //  Vec3
};
