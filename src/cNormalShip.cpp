#include "cNormalShip.hpp"


cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch, bool awake) : cEnemy(map, ch)
{
	mWidth = 64; mHeight = 64;
	mTexturePath = "enemy1.png";
	mAwake = awake;
	if (!mTexture.Load(mTexturePath.c_str(), GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	mPhysics = std::make_shared<cPhysics>(mForce, mMaxSpeed, mSpeed);
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(ch));
}


cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch, int life, bool awake) : cEnemy(map, ch, life)
{
	mWidth = 64; mHeight = 64;
	mTexturePath = "enemy1.png";
	mAwake = awake;
	if (!mTexture.Load(mTexturePath.c_str(), GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	mPhysics = std::make_shared<cPhysics>(mForce, mMaxSpeed, mSpeed);
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(ch));
}
#include <iostream>
cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake) 
: cEnemy(map, ch, life)
{
	mWidth = 64; mHeight = 64;
	mTexturePath = "enemy1.png";
	setInitialTilePosition(tilePosition);
	mAwake = awake;
	if (!mTexture.Load(mTexturePath.c_str(), GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	mPhysics = std::make_shared<cPhysics>(mForce, mMaxSpeed, mSpeed);
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(ch));
}

void cNormalShip::doLogic(float dt)
{
	if (mAwake) {
		if (!mProjectiles[0]->mAwake) {
			mProjectiles[0]->mWPosition = mProjectiles[1]->mWPosition = mProjectiles[2]->mWPosition = this->mWPosition;
			mProjectiles[0]->mAwake = mProjectiles[1]->mAwake = mProjectiles[2]->mAwake = true;
			mProjectiles[1]->changePhysics(Vec3(0.0f, -0.5f), Vec3(0.0f, -3.0f), Vec3(0.0f, -0.5f));
			mProjectiles[2]->changePhysics(Vec3(0.5f, -0.5f), Vec3(3.0f, -3.0f), Vec3(0.5f, -0.5f));
		}		
		move(mPhysics->mSpeed, dt);
		mPhysics->update(dt);
		mProjectiles[0]->doLogic(dt); mProjectiles[1]->doLogic(dt); mProjectiles[2]->doLogic(dt);
	}
}

void cNormalShip::move(Vec3 const& speed, float dt)
{
	mWPosition += (speed * dt);
}

void cNormalShip::draw()
{
	if (mAwake) {
		Vec3 const screen = mCoordChanges.WorldToScreen(mWPosition);
		glPushMatrix();
		glTranslatef(screen.x, screen.y, 0);
		mTexture.drawAlternative(Vec3(0, 0), Vec3(1, 1), Vec3(0, 0), Vec3(mWidth, mHeight));
		glPopMatrix();
		mProjectiles[0]->draw(); mProjectiles[1]->draw(); mProjectiles[2]->draw();

	}
}

