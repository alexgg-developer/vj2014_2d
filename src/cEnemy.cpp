#include "cEnemy.hpp"

cEnemy::cEnemy(cScene const& map, cCoordChanges const& ch, int life, std::shared_ptr<cPhysics>& physics) : mMap(map), mLife(life), mCoordChanges(ch), mPhysics(physics)
{
	//mInitialWPosition = mCoordChanges.TileToWorld(Vec3(10, 10));
}

void cEnemy::setInitialTilePosition(Vec3 const& tilePosition)
{
	mWPosition = mCoordChanges.TileToWorld(tilePosition);
}
void cEnemy::draw()
{
	if (mAwake) {
		Vec3 const screen = mCoordChanges.WorldToScreen(mWPosition);
		glPushMatrix();
		glTranslatef(screen.x, screen.y, 0);
		mTexture.drawAlternative(Vec3(0, 0), Vec3(1, 1), Vec3(0, 0), Vec3(mWidth, mHeight));
		glPopMatrix();
	}
}
