#pragma once

#include "cEnemy.hpp"
#include "cNormalProjectile.hpp"
#include <vector>
#include <memory>

struct cNormalShip: public cEnemy {

	const Vec3 mSpeed	 = Vec3(-50.0f, 0);
	const Vec3 mForce	 = Vec3(-100.0f, 0);
	const Vec3 mMaxSpeed = Vec3(-100.0f, 0);
	std::vector<std::shared_ptr<cNormalProjectile>> mProjectiles;
	cNormalShip(cScene const& map, cCoordChanges const& ch, bool awake);
	cNormalShip(cScene const& map, cCoordChanges const& ch, int life, bool awake);
	cNormalShip(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake);
	void doLogic(float dt);
	void draw();

private:
	void move(Vec3 const& speed, float dt);
};
