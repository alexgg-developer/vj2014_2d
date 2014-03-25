#include "cNormalShip.hpp"

cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch) : cEnemy(map, ch)
{
	mWidth = 64; mHeight = 64;
	if (!mTexture.Load("CrateScaled.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
}


cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch, int life) : cEnemy(map, ch, life)
{
	mWidth = 64; mHeight = 64;
	if (!mTexture.Load("CrateScaled.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
}

cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition) : cEnemy(map, ch, life)
{
	mWidth = 64; mHeight = 64;
	setInitialTilePosition(tilePosition);
	if (!mTexture.Load("enemy1.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
}
