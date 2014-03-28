#pragma once
#include <memory>
#include "Vec3.hpp"

struct cPhysics
{
	Vec3 mForce, mInitialForce;
	Vec3 mMaxSpeed, mInitialMaxSpeed;
	Vec3 mSpeed, mInitialSpeed;	
	//cPhysics() : mForce(Vec3(0.0f, 0.0f)), mMaxSpeed(Vec3(0.0f, 0.0f)), mSpeed(Vec3(0.0f, 0.0f)) {}
	cPhysics(std::shared_ptr<cPhysics> const & physics);
	cPhysics(Vec3 const & force, Vec3 const & maxSpeed) : mForce(force), mMaxSpeed(maxSpeed), mSpeed(Vec3(0.0f, 0.0f)), mInitialForce(mForce), mInitialMaxSpeed(mMaxSpeed), mInitialSpeed(mSpeed) {}
	cPhysics(Vec3 const & force, Vec3 const & maxSpeed, Vec3 const & speed) : mForce(force), mMaxSpeed(maxSpeed), mSpeed(speed), mInitialForce(mForce), mInitialMaxSpeed(mMaxSpeed), mInitialSpeed(mSpeed) {}
	void update(float dt);
	void changeDirection(Vec3 const & direction);
};