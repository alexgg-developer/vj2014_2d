#include "cNormalProjectile.hpp"
#include <iostream>

cNormalProjectile::cNormalProjectile(cCoordChanges const& ch) : cProjectile(ch)
{
	mWidth = 19; mHeight = 19;
	mAwake = false;
	mDamage  = 1;
	if (!mTexture.Load("1stProjectile.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}

	mSpeed = Vec3(-0.5f, -0.5f);
	mForce = Vec3(-0.5f, -0.5f);
	mMaxSpeed = Vec3(-3.0f, -3.0f);
	mPhysics = std::make_shared<cPhysics>(mForce, mMaxSpeed, mSpeed);
}

void cNormalProjectile::doLogic(float dt)
{
	if (mAwake) {
		move(mPhysics->mSpeed);
		mPhysics->update(dt);		
	}
}

void cNormalProjectile::move(Vec3 const& speed)
{
	mWPosition += speed;
}

void cNormalProjectile::changePhysics(Vec3 const& force, Vec3 const& maxSpeed, Vec3 const& speed)
{
	mPhysics->mForce = force;
	mPhysics->mMaxSpeed = maxSpeed;
	mPhysics->mSpeed = speed;
}