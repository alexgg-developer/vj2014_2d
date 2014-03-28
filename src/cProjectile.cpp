#include "cProjectile.hpp"

void cProjectile::draw() {
	if (mAwake) {
		Vec3 const screen = mCoordChange.WorldToScreen(posW);
		glPushMatrix();
		glTranslatef(screen.x, screen.y, 0);
		mText.drawAlternative(Vec3(0, 0), Vec3(1, 1), Vec3(0, 0), Vec3(w, h));
		glPopMatrix();
	}
}

void cProjectile::changePhysics(Vec3 const& force, Vec3 const& maxSpeed, Vec3 const& speed) {
	mPhysics->mForce = force;
	mPhysics->mMaxSpeed = maxSpeed;
	mPhysics->mSpeed = speed;
}

void cProjectile::move(Vec3 const& speed, float const dt) {
	posW += (speed * dt);
}
void cProjectile::doLogic(float dt)
{
	if (mAwake) {
		move(mPhysics->mSpeed, dt);
		mPhysics->update(dt);		
	}
}