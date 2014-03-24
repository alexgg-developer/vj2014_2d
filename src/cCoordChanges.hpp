#pragma once
#include "Vec3.hpp"

struct cCoordChanges {
  cCoordChanges();

  Vec3 WorldToScreen(float const x, float const y) const;
  /// In integer units
  Vec3 WorldToTile  (float const x, float const y) const;
  Vec3 ScreenToWorld(float const x, float const y) const;
  Vec3 TileToWorld  (float const tx, float const ty) const;
  
  unsigned int const getTileSize() const { return mTileSize;}
  unsigned int const getBlockSize() const { return mBlockSize;}
  unsigned int const getOriginX() const { return mOriginX;}
  unsigned int const getOriginY() const { return mOriginY;}
protected:
  unsigned int const mTileSize;
  unsigned int const mBlockSize;
  unsigned int const mOriginX;
  unsigned int const mOriginY;
};
