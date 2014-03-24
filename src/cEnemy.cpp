#include "cEnemy.hpp"

cEnemy::cEnemy(cScene const& map, cCoordChanges const& ch, int life) : mMap(map), mLife(life), mWidth(64), mHeight(64), mCoordChanges(ch)
{
	mInitialWPosition = mCoordChanges.TileToWorld(Vec3(10, 10));
	if (!mTexture.Load("enemy1.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
}

void cEnemy::draw()
{
	Vec3 screen = mCoordChanges.WorldToScreen(mInitialWPosition);
	mTexture.Draw(0, 0, 1, 1, screen, Vec3(screen.x + mWidth, screen.y + mHeight));
}
