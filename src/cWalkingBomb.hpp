#pragma once

#include <vector>
#include <memory>
#include "cEnemy.hpp"
#include "cPlayer.hpp"

struct cWalkingBomb: public cEnemy {

	const Vec3 mSpeed	 = Vec3(-25.0f, 0);
	const Vec3 mForce	 = Vec3(-200.0f, 0);
	const Vec3 mMaxSpeed = Vec3(-100.0f, 0);
	cPlayer const & mPlayer;
	int mDamage;
	cWalkingBomb(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake, cPlayer const & target);
	void doLogic(float dt);
	void draw();

private:
	void move(Vec3 const& speed, float dt);
	void followTheTarget();
};
