#pragma once

#include "cEnemy.hpp"

struct cNormalShip: public cEnemy {
	cNormalShip(cScene const& map, cCoordChanges const& ch);
	cNormalShip(cScene const& map, cCoordChanges const& ch, int life);
	cNormalShip(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition);
};