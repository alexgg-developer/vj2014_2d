#pragma once
#include "Globals.hpp"
#include "cTexture.hpp"
#include <iostream>
#include "Position.hpp"
#include "cScene.hpp"

struct cEnemy {
	int mLife;
	cTexture mTexture;
	Position mInitialWPosition;
	int mWidth, mHeight;
	cScene const& mMap;
	cEnemy(cScene const& map): mMap(map) {};
	cEnemy(cScene const& map, int life);
	void draw();
};