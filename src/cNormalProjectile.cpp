#include "cNormalProjectile.hpp"
#include <iostream>

cNormalProjectile::cNormalProjectile(cPlayer& pl, cScene const& map, cCoordChanges const& ch)
 : cProjectile(pl, map, ch)
{
	w = 19; h = 19;
	mAwake = false;
	mDamage  = 1;
	if (!mText.Load("1stProjectile.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}

	mPhysics = std::make_shared<cPhysics>(Vec3(-0.5f, -0.5f), Vec3(-3.0f, -3.0f), Vec3(-0.5f, -0.5f));
}