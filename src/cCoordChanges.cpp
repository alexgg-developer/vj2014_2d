#include "cCoordChanges.hpp"
#include <assert.h>

cCoordChanges::cCoordChanges() : mTileSize(16), mBlockSize(24), mOriginX(2*mTileSize), mOriginY(mTileSize)  {}


Vec3 cCoordChanges::WorldToScreen(float const x, float const y) const {
  return Vec3(x + float(mOriginX),
	  y+float(mOriginY+(mBlockSize-mTileSize))); }
Vec3 cCoordChanges::WorldToTile  (float const x, float const y) const {
    return Vec3(static_cast<int>(x/mTileSize), static_cast<int>(y/mTileSize)); }
Vec3 cCoordChanges::ScreenToWorld(float const x, float const y) const {
	assert(0 && "Not yet implemented");
	return Vec3(float(0),float(0)); }
Vec3 cCoordChanges::TileToWorld(float const tx, float const ty) const {
  return Vec3(tx * mTileSize, ty * mTileSize); }
