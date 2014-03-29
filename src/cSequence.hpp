#pragma once
#include "cTexture.hpp"
#include "cAni.hpp"
#include <functional>
#include <vector>
#include <memory>

struct cSequence {
  cSequence(Vec3 const& aScreenPos, Vec3 const& aScreenPos1,  cTexture const& aText, cAni const& aAni, std::function<void()> aOnEndAni = std::function<void()>());
  void doLogic(float const dt);
  void draw(float const dt) const;
  void reset(float const t);
  void setOnEndAni(std::function<void()> const& aOnEndAni) { mOnEndAni = aOnEndAni; }
protected:
  cTexture mText;
  cAni mAni;
  std::function<void()> mOnEndAni;
  float mInitT; /// -1 indicates not playing
  Vec3 mScreenPos0, mScreenPos1;
};

/// Composes sequences linearly
struct cSequence_Composed {
  cSequence_Composed(std::function<void()> aOnEndAni = std::function<void()>()) : mOnEnd(aOnEndAni) {}

  void addNextSeq(cSequence const& seq);
  void jumpToNextSeq(int next);

  void doLogic(float const dt);
  void draw(float const dt) const;
  void reset(float const t);
protected:
  std::vector<cSequence> mSequences;
  std::function<void()> mOnEnd;
  std::size_t mActiveSequence=0;
};
