#pragma once

#include <vector>
#include <memory>
#include "cEnemy.hpp"
#include "cPlayer.hpp"

struct cWalkingBomb: public cEnemy {
	int mDamage;
	cWalkingBomb(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake, cPlayer& target);
	virtual void doLogic(float const t, float const dt) override;

private:
	void followTheTarget();
};
