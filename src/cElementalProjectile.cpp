#include "cElementalProjectile.hpp"
#include <iostream>

cElementalProjectile::cElementalProjectile(cCoordChanges const& ch, KindOfElement element) : cProjectile(ch), mElement(element)
{
	mWidth = 163/3; mHeight = 53/3;
	mAwake = false;
	switch (mElement){
		case FIRE:
			if (!mTexture.Load("FireAttack.png", GL_RGBA)) {
				std::cerr << "Texture did not load" << std::endl;
			}
			break;
		case ICE:
			if (!mTexture.Load("IceAttack.png", GL_RGBA)) {
				std::cerr << "Texture did not load" << std::endl;
			}
			break;
		case ELECTRIC:
			if (!mTexture.Load("ElectricAttack.png", GL_RGBA)) {
				std::cerr << "Texture did not load" << std::endl;
			}
			break;
	}

	mSpeed = Vec3(-2.5f, -2.5f);
	mForce = Vec3(-0.5f, -0.5f);
	mMaxSpeed = Vec3(-5.0f, -5.0f);
	mPhysics = std::make_shared<cPhysics>(mForce, mMaxSpeed, mSpeed);
}

void cElementalProjectile::doLogic(float dt)
{
	if (mAwake) {
		move(mPhysics->mSpeed);
		mPhysics->update(dt);		
	}
}

void cElementalProjectile::move(Vec3 const& speed)
{
	mWPosition += speed;
}

void cElementalProjectile::changePhysics(Vec3 const& force, Vec3 const& maxSpeed, Vec3 const& speed)
{
	mPhysics->mForce = force;
	mPhysics->mMaxSpeed = maxSpeed;
	mPhysics->mSpeed = speed;
}