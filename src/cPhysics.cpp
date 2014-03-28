#include "cPhysics.hpp"
#include <cmath>

cPhysics::cPhysics(std::shared_ptr<cPhysics> const & physics)
{
	mInitialForce = mForce = physics->mForce;
	mInitialMaxSpeed = mMaxSpeed = physics->mMaxSpeed;
	mInitialSpeed = mSpeed = physics->mSpeed;
}
void cPhysics::update(float dt)
{
	Vec3 speed = mForce * dt;
	//Esta mal hecho pero cuela de momento.
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

void cPhysics::changeDirection(Vec3 const & direction)
{
	mForce.x = direction.x * std::fabs(mInitialForce.x);
	mForce.y = direction.y * std::fabs(mInitialForce.y);
	mForce.z = direction.z * std::fabs(mInitialForce.z);

	mSpeed.x = direction.x * std::fabs(mInitialSpeed.x);
	mSpeed.y = direction.y * std::fabs(mInitialSpeed.y);
	mSpeed.z = direction.z * std::fabs(mInitialSpeed.z);

	mMaxSpeed.x = direction.x * std::fabs(mInitialMaxSpeed.x);
	mMaxSpeed.y = direction.y * std::fabs(mInitialMaxSpeed.y);
	mMaxSpeed.z = direction.z * std::fabs(mInitialMaxSpeed.z);
}
