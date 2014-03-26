#pragma once
#include <memory>
#include "cPhysics.hpp"
#include "cTexture.hpp"
#include "Vec3.hpp"
#include "cCoordChanges.hpp"

struct cProjectile
{
	std::shared_ptr<cPhysics> mPhysics;
	cTexture mTexture;
	cCoordChanges mCoordChanges;
	Vec3 mWPosition;
	Vec3 mForce, mMaxSpeed, mSpeed;
	bool mAwake;
	int mDamage;
	int mWidth, mHeight;

	cProjectile(cCoordChanges const& ch) : mCoordChanges(ch) {}
	void draw();

};