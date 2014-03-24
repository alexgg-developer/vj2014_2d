#pragma once
#include "Globals.hpp"
#include "cTexture.hpp"
#include <iostream>
#include "Vec3.hpp"
#include "cScene.hpp"

struct cEnemy {
	int mLife;
	cTexture mTexture;
	Vec3 mInitialWPosition;
	int mWidth, mHeight;
	cScene const& mMap;
	cEnemy(cScene const& map, cCoordChanges const& ch): mMap(map), mCoordChanges(ch) {};
	cEnemy(cScene const& map, cCoordChanges const& ch, int life);
	void draw();
protected:
	cCoordChanges const& mCoordChanges;
};