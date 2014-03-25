#include "cEnemy.hpp"

cEnemy::cEnemy(cScene const& map, cCoordChanges const& ch, int life) : mMap(map), mLife(life), mCoordChanges(ch)
{
	//mInitialWPosition = mCoordChanges.TileToWorld(Vec3(10, 10));
}

void cEnemy::setInitialTilePosition(Vec3 const& tilePosition)
{
	mInitialWPosition = mCoordChanges.TileToWorld(tilePosition);
}
void cEnemy::draw()
{
	Vec3 const screen = mCoordChanges.WorldToScreen(mInitialWPosition);
	glPushMatrix();
	glTranslatef(screen.x, screen.y, 0);
	mTexture.drawAlternative(Vec3(0, 0), Vec3(1, 1), Vec3(0, 0), Vec3(mWidth, mHeight));
	glPopMatrix();
}
