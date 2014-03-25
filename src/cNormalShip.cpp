#include "cNormalShip.hpp"


cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch, bool awake) : cEnemy(map, ch, std::shared_ptr<cPhysics>(new cPhysics(Vec3(-0.5, 0), Vec3(-3, 0))))
{
	mWidth = 64; mHeight = 64;
	mTexturePath = "enemy1.png";
	mAwake = awake;
	if (!mTexture.Load(mTexturePath.c_str(), GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
}


cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch, int life, bool awake) : cEnemy(map, ch, life, std::shared_ptr<cPhysics>(new cPhysics(Vec3(-0.5, 0), Vec3(-3, 0))))
{
	mWidth = 64; mHeight = 64;
	mTexturePath = "enemy1.png";
	mAwake = awake;
	if (!mTexture.Load(mTexturePath.c_str(), GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
}

cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake) 
: cEnemy(map, ch, life, std::shared_ptr<cPhysics>(new cPhysics(Vec3(-0.5, 0), Vec3(-3, 0))))
{
	mWidth = 64; mHeight = 64;
	mTexturePath = "enemy1.png";
	setInitialTilePosition(tilePosition);
	mAwake = awake;
	if (!mTexture.Load(mTexturePath.c_str(), GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	//mPhysics(new cPhysics(Vec3(-1.0f, 0.0f), Vec3(-3.0f, 0.0)));
	
}

void cNormalShip::doLogic(float dt)
{
	if (mAwake) {
		move(mPhysics->mSpeed);
		mPhysics->update(dt);
	}
}

void cNormalShip::move(Vec3 const& speed)
{
	mWPosition += speed;
}

