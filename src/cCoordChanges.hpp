#pragma once
#include "cScene.hpp"
#include "Vec3.hpp"

struct cCoordChanges {
  cCoordChanges(cScene const& aSc);

  Vec3 WorldToScreen(float const x, float const y) const;
  /// In integer units
  Vec3 WorldToTile  (float const x, float const y) const;
  Vec3 ScreenToWorld(float const x, float const y) const;
  Vec3 TileToWorld  (float const tx, float const ty) const;
protected:
  cScene const& mScene;
};
