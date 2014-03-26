#include "cProjectile.hpp"

void cProjectile::draw()
{
	if (mAwake) {
		Vec3 const screen = mCoordChanges.WorldToScreen(mWPosition);
		glPushMatrix();
		glTranslatef(screen.x, screen.y, 0);
		mTexture.drawAlternative(Vec3(0, 0), Vec3(1, 1), Vec3(0, 0), Vec3(mWidth, mHeight));
		glPopMatrix();
	}
}
