#pragma once

#include "cEnemy.hpp"

struct cNormalShip: public cEnemy {

	const Vec3 mSpeed = Vec3(-0.5, 0);
	cNormalShip(cScene const& map, cCoordChanges const& ch, bool awake);
	cNormalShip(cScene const& map, cCoordChanges const& ch, int life, bool awake);
	cNormalShip(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake);
	void doLogic(float dt);

private:
	void move(Vec3 const& speed);
};
