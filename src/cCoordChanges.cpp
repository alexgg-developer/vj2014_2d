#include "cCoordChanges.hpp"
#include <assert.h>

cCoordChanges::cCoordChanges() : mTileSize(16), mBlockSize(24), mOriginX(2*mTileSize), mOriginY(mTileSize)  {}


Vec3 cCoordChanges::WorldToScreen(Vec3 const& v) const {
  return Vec3(v.x + float(mOriginX),
	  v.y+float(mOriginY+(mBlockSize-mTileSize))); }
Vec3 cCoordChanges::WorldToTile  (Vec3 const& v) const {
    return Vec3(static_cast<int>(v.x/mTileSize), static_cast<int>(v.y/mTileSize)); }
Vec3 cCoordChanges::ScreenToWorld(Vec3 const& v) const {
	assert(0 && "Not yet implemented");
	return Vec3(float(0),float(0)); }
Vec3 cCoordChanges::TileToWorld(Vec3 const& v) const {
  return Vec3(v.x * mTileSize, v.y * mTileSize); }
