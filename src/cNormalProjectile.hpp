#pragma once
#include "cProjectile.hpp"

struct cNormalProjectile: public cProjectile
{
	cNormalProjectile(cCoordChanges const& ch);
	void doLogic(float dt);
	void changePhysics(Vec3 const& force, Vec3 const& maxSpeed, Vec3 const& speed);
private:
	void move(Vec3 const& speed);
};