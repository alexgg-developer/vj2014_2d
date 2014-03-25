#pragma once
#include "Vec3.hpp"

struct cFrame {
  cFrame(Vec3 const& aBegin, Vec3 const& aEnd) : mBegin(aBegin), mEnd(aEnd) {}
  Vec3 mBegin, mEnd;
};
