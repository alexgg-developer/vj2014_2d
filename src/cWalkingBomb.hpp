#pragma once

#include <vector>
#include <memory>
#include "cEnemy.hpp"
#include "cPlayer.hpp"

struct cWalkingBomb: public cEnemy {
	cPlayer const & mPlayer;
	int mDamage;
	cWalkingBomb(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake, cPlayer const & target);
	void doLogic(float dt);
	void draw();

private:
	void followTheTarget();
};
