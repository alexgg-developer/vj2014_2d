#pragma once
#include "cTexture.hpp"
#include "cAni.hpp"
#include <functional>

struct cSequence {
  cSequence(cTexture const& aText, cAni const& aAni, std::function<void()> aOnEndAni = std::function<void()>());
  void doLogic(float const dt);
  void draw(float const dt) const;
  void reset();
  void compose(cSequence& other);
protected:
  cTexture mText;
  cAni mAni;
  std::function<void()> mOnEndAni;
  float mInitT; /// -1 indicates not playing
};
