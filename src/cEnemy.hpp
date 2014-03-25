#pragma once
#include <iostream>
#include "Globals.hpp"
#include "cTexture.hpp"
#include "Vec3.hpp"
#include "cScene.hpp"

struct cEnemy {
	int mLife;
	int mWidth, mHeight;
	float mOrientation;
	cTexture mTexture;
	cScene const& mMap;
	Vec3 mInitialWPosition;
	cEnemy(cScene const& map, cCoordChanges const& ch): mMap(map), mCoordChanges(ch), mLife(1) {};
	cEnemy(cScene const& map, cCoordChanges const& ch, int life);
	void setInitialTilePosition(Vec3 const& tilePosition);
	virtual ~cEnemy() {};
	virtual void draw();
protected:
	cCoordChanges const& mCoordChanges;
};