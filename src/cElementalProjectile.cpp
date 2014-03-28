#include "cElementalProjectile.hpp"
#include <iostream>

cElementalProjectile::cElementalProjectile(cScene const& map, cCoordChanges const& ch, KindOfElement element) : cProjectile(map, ch), mElement(element)
{
	w = 163/3; h = 53/3;
	mAwake = false;
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

	mPhysics = std::make_shared<cPhysics>(Vec3(-0.5f, -0.5f), Vec3(-5.0f, -5.0f), Vec3(-2.5f, -2.5f));
}