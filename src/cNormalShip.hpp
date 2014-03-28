#pragma once

#include "cEnemy.hpp"
#include "cNormalProjectile.hpp"
#include <vector>
#include <memory>

struct cNormalShip: public cEnemy {
	cNormalShip(cScene const& map, cCoordChanges const& ch, bool awake);
	cNormalShip(cScene const& map, cCoordChanges const& ch, int life, bool awake);
	cNormalShip(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake);
	void doLogic(float dt);
	void draw();

protected:
	std::vector<std::shared_ptr<cNormalProjectile>> mProjectiles;
};
