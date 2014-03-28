#pragma once
#include "cProjectile.hpp"

struct cElementalProjectile: public cProjectile
{
	enum KindOfElement{ FIRE, ICE, ELECTRIC };
	KindOfElement mElement;

	cElementalProjectile(cCoordChanges const& ch, KindOfElement element);
	void doLogic(float dt);
	void changePhysics(Vec3 const& force, Vec3 const& maxSpeed, Vec3 const& speed);
private:
	void move(Vec3 const& speed);
};