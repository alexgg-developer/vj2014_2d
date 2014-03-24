#include "cCoordChanges.hpp"
#include <assert.h>

cCoordChanges::cCoordChanges(cScene const& aSc) : mScene(aSc) {}


Vec3 cCoordChanges::WorldToScreen(float const x, float const y) const {
  return Vec3(x + float(mScene.getOriginX()), y+float(mScene.getOriginY()+(mScene.getBlockSize()-mScene.getTileSize())); }
Vec3 cCoordChanges::WorldToTile  (float const x, float const y) const {
    return Vec3(static_cast<int>(x/mScene.getTileSize()), static_cast<int>(y/mScene.getTileSize())); }
Vec3 cCoordChanges::ScreenToWorld(float const x, float const y) const {
	assert(0 && "Not yet implemented");
	return Vec3(float(0),float(0)); }
Vec3 cCoordChanges::TileToWorld(float const tx, float const ty) const {
  return Vec3(tx * mScene.getTileSize(), ty * mScene.getTileSize()); }
