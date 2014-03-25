#pragma once
#include <memory>
#include "Vec3.hpp"

struct cPhysics
{
	Vec3 mForce;
	Vec3 mMaxSpeed;
	Vec3 mSpeed;	
	//cPhysics() : mForce(Vec3(0.0f, 0.0f)), mMaxSpeed(Vec3(0.0f, 0.0f)), mSpeed(Vec3(0.0f, 0.0f)) {}
	cPhysics(std::unique_ptr<cPhysics> const & physics);
	cPhysics(Vec3 const & force, Vec3 const & maxSpeed) : mForce(force), mMaxSpeed(maxSpeed), mSpeed(Vec3(0.0f, 0.0f)) {}
	void update(float dt);
};