#include "cProjectile.hpp"
#include "cExplosion.hpp"

void cProjectile::Draw(float const t, float const dt) const {
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
void cProjectile::doLogic(float const t, float const dt)
{
	if (mAwake) {
		move(mPhysics->mSpeed, dt);
		mPhysics->update(dt);		
    if(mAffectsProta && CollidesWithPlayer()) {
       cExplosion::addExplosion(mMap, mCoordChange, posW);	
       mLife=-1;//Delete itself
    }
    //TODO: Delete enemies
    /* else if(mAffectsEnemies && CollidesWithPlayer()) {
       cExplosion::addExplosion(mMap, mCoordChange, posW);	
       mLife=-1;//Delete itself
    }*/
	}
}