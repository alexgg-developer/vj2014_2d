#include "cElementalProjectile.hpp"
#include <iostream>

cElementalProjectile::cElementalProjectile(cPlayer& pl, cScene const& map, cCoordChanges const& ch, KindOfElement element)
 : cProjectile(pl, map, ch), mElement(element)
{
	w = 163/3; h = 53/3;
	switch (mElement){
		case FIRE:
			if (!mText.Load("FireAttack.png", GL_RGBA)) {
				std::cerr << "Texture did not load" << std::endl;
			}
			break;
		case ICE:
			if (!mText.Load("IceAttack.png", GL_RGBA)) {
				std::cerr << "Texture did not load" << std::endl;
			}
			break;
		case ELECTRIC:
			if (!mText.Load("ElectricAttack.png", GL_RGBA)) {
				std::cerr << "Texture did not load" << std::endl;
			}
			break;
	}
  static const float mult = 30.0f;
	mPhysics = std::make_shared<cPhysics>(Vec3(-0.5f, -0.5f)*mult, Vec3(-5.0f, -5.0f)*mult, Vec3(-2.5f, -2.5f)*mult);
}