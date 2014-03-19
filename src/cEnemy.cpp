#include "cEnemy.hpp"

cEnemy::cEnemy(cScene const& map, int life) : mMap(map), mLife(life), mWidth(64), mHeight(64)
{ 
	int x, y; 
	std::tie(x, y) = map.TileToWorld(10, 10);
	mInitialWPosition = Position(x, y); 
	if (!mTexture.Load("enemy1.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
}

void cEnemy::draw()
{
	float screen_x, screen_y;
	std::tie(screen_x, screen_y) = mMap.WorldToScreen(mInitialWPosition.x, mInitialWPosition.y);
	mTexture.Draw(0, 0, 1, 1, screen_x, screen_y, screen_x + mWidth, screen_y + mHeight);
}
