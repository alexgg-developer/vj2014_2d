#include "cWalkingBomb.hpp"
#include <iostream>

cWalkingBomb::cWalkingBomb(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake, cPlayer const & target)
: cEnemy(map, ch, life), mPlayer(target)
{
	mAwake = awake;
	w = 16; h = 19;
	setInitialTilePosition(tilePosition);
	if (!mText.Load("WalkingBomb.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	mPhysics = std::make_shared<cPhysics>(Vec3(-200.0f, 0), Vec3(-100.0f, 0), Vec3(-25.0f, 0));
	mDamage = 2;
}

void cWalkingBomb::doLogic(float const t, float const dt)
{
	if (mAwake) {	
		move(mPhysics->mSpeed, dt);
		followTheTarget();
		mPhysics->update(dt);
	}
}

void cWalkingBomb::draw()
{
	if (mAwake) {
		Vec3 const screen = mCoordChange.WorldToScreen(posW);
		glPushMatrix();
		glTranslatef(screen.x, screen.y, 0);
		mText.drawAlternative(Vec3(0, 0), Vec3(1, 1), Vec3(0, 0), Vec3(w, h));
		glPopMatrix();
	}
}

void cWalkingBomb::followTheTarget()
{
	if (mPlayer.GetPosition_W().x < posW.x) {
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


