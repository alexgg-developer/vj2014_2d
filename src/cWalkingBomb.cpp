#include "cWalkingBomb.hpp"
#include <iostream>

cWalkingBomb::cWalkingBomb(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake, cPlayer const & target)
: cEnemy(map, ch, life), mPlayer(target)
{
	mAwake = awake;
	mWidth = 16; mHeight = 19;
	mTexturePath = "WalkingBomb.png";
	setInitialTilePosition(tilePosition);
	if (!mTexture.Load(mTexturePath.c_str(), GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	mPhysics = std::make_shared<cPhysics>(mForce, mMaxSpeed, mSpeed);
	mDamage = 2;
}

void cWalkingBomb::doLogic(float dt)
{
	if (mAwake) {	
		move(mPhysics->mSpeed, dt);
		followTheTarget();
		mPhysics->update(dt);
	}
}

void cWalkingBomb::move(Vec3 const& speed, float dt)
{
	mWPosition += (speed * dt);
}

void cWalkingBomb::draw()
{
	if (mAwake) {
		Vec3 const screen = mCoordChanges.WorldToScreen(mWPosition);
		glPushMatrix();
		glTranslatef(screen.x, screen.y, 0);
		mTexture.drawAlternative(Vec3(0, 0), Vec3(1, 1), Vec3(0, 0), Vec3(mWidth, mHeight));
		glPopMatrix();
	}
}

void cWalkingBomb::followTheTarget()
{
	if (mPlayer.GetPosition_W().x < mWPosition.x) {
		if (mPhysics->mForce.x > 0) {
			mPhysics->mSpeed.x = 0.0f;
			mPhysics->mForce.x = -mPhysics->mForce.x;
			mPhysics->mMaxSpeed.x = -mPhysics->mMaxSpeed.x;
		}
	}
	else {
		if (mPhysics->mForce.x < 0) {
			mPhysics->mSpeed.x = 0.0f;
			mPhysics->mForce.x = -mPhysics->mForce.x;
			mPhysics->mMaxSpeed.x = -mPhysics->mMaxSpeed.x;
		}
	}
}


