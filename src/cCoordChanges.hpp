#pragma once
#include "Vec3.hpp"

struct cCoordChanges {
  cCoordChanges();

  Vec3 WorldToScreen(Vec3 const& v) const;
  /// In integer units
  Vec3 WorldToTile  (Vec3 const& v) const;
  Vec3 ScreenToWorld(Vec3 const& v) const;
  Vec3 TileToWorld  (Vec3 const& v) const;
  
  unsigned int const GetTileSize() const { return mTileSize;}
  unsigned int const getBlockSize() const { return mBlockSize;}
  unsigned int const getOriginX() const { return mOriginX;}
  unsigned int const getOriginY() const { return mOriginY;}
protected:
  unsigned int const mTileSize;
  unsigned int const mBlockSize;
  unsigned int const mOriginX;
  unsigned int const mOriginY;
};
