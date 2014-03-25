#include "cPhysics.hpp"

cPhysics::cPhysics(std::unique_ptr<cPhysics> const & physics)
{
	mForce = physics->mForce;
	mMaxSpeed = physics->mMaxSpeed;
	mSpeed = physics->mSpeed;
}
void cPhysics::update(float dt)
{
	Vec3 speed = mForce * dt;
	if (speed.x < 0.0f) {
		mSpeed.x += max(speed.x, mMaxSpeed.x);
	}
	else {
		mSpeed.x += min(speed.x, mMaxSpeed.x);
	}

	if (speed.y < 0.0f) {
		mSpeed.y += max(speed.y, mMaxSpeed.y);
	}
	else {
		mSpeed.y += min(speed.y, mMaxSpeed.y);
	}
}
