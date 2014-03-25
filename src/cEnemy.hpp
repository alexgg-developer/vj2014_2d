#pragma once
#include <iostream>
#include <string>
#include <memory>

#include "Globals.hpp"
#include "cTexture.hpp"
#include "Vec3.hpp"
#include "cScene.hpp"
#include "cPhysics.hpp"

struct cEnemy {
	int mLife;
	int mWidth, mHeight;
	float mOrientation;
	cTexture mTexture;
	cScene const& mMap;
	//cPhysics mPhysics;
	std::shared_ptr<cPhysics> mPhysics;
	Vec3 mWPosition;
	std::string mTexturePath;
	bool mAwake;
	cEnemy(cScene const& map, cCoordChanges const& ch, std::shared_ptr<cPhysics>& physics) : mMap(map), mCoordChanges(ch), mLife(1), mPhysics(physics) {};
	cEnemy(cScene const& map, cCoordChanges const& ch, int life, std::shared_ptr<cPhysics>& physics);
	void setInitialTilePosition(Vec3 const& tilePosition);
	virtual void doLogic(float dt) = 0;
	virtual void draw();
protected:
	cCoordChanges const& mCoordChanges;
};