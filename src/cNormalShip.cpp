#include "cNormalShip.hpp"
#include "cNormalProjectile.hpp"
#include "cPlayer.hpp"
#include "cPhysics.hpp"
#include "cCoordChanges.hpp"
#include <iostream>

cNormalShip::cNormalShip(cPlayer& pl, cScene const& map, cCoordChanges const& ch, bool awake) : cEnemy(pl, map, ch)
{
	w = 64; h = 64;
	mAwake = awake;
	if (!mText.Load("enemy1.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	mPhysics = std::make_shared<cPhysics>(Vec3(-100.0f, 0), Vec3(-100.0f, 0), Vec3(-50.0f, 0));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(pl, map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(pl, map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(pl, map, ch));
}


cNormalShip::cNormalShip(cPlayer& pl, cScene const& map, cCoordChanges const& ch, int life, bool awake)
 : cEnemy(pl, map, ch, life) {
	w = 64; h = 64;
	mAwake = awake;
	if (!mText.Load("enemy1.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	mPhysics = std::make_shared<cPhysics>(Vec3(-100.0f, 0), Vec3(-100.0f, 0), Vec3(-50.0f, 0));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(pl, map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(pl, map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(pl, map, ch));
}
#include <iostream>
cNormalShip::cNormalShip(cPlayer& pl, cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake) 
: cEnemy(pl, map, ch, life) {
	w = 64; h = 64;
	setInitialTilePosition(tilePosition);
	mAwake = awake;
	if (!mText.Load("enemy1.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	mPhysics = std::make_shared<cPhysics>(Vec3(-100.0f, 0), Vec3(-100.0f, 0), Vec3(-50.0f, 0));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(pl, map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(pl, map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(pl, map, ch));
}

void cNormalShip::doLogic(float const t, float const dt)
{
	if (mAwake) {
		if (!mProjectiles[0]->Awake()) {
			mProjectiles[0]->SetPosition_W(this->posW);
			mProjectiles[1]->SetPosition_W(this->posW);
			mProjectiles[2]->SetPosition_W(this->posW);
			mProjectiles[0]->mAwake = mProjectiles[1]->mAwake = mProjectiles[2]->mAwake = true;
			mProjectiles[0]->changePhysics(Vec3( 0.5f, -0.5f)*10.0f, Vec3( 30.0f, -30.0f), Vec3( 1.0f, -1.0f)*20.0f);
			mProjectiles[1]->changePhysics(Vec3( 0.0f, -0.5f)*10.0f, Vec3(  0.0f, -30.0f), Vec3( 0.0f, -1.0f)*20.0f);
			mProjectiles[2]->changePhysics(Vec3(-0.5f, -0.5f)*10.0f, Vec3(-30.0f, -30.0f), Vec3(-1.0f, -1.0f)*20.0f);
		}		
		move(mPhysics->mSpeed, dt);
		mPhysics->update(dt);
		mProjectiles[0]->doLogic(t,dt); mProjectiles[1]->doLogic(t,dt); mProjectiles[2]->doLogic(t,dt);
	}
}


void cNormalShip::Draw(float const t, float const dt) const {
	if (mAwake) {
  	Vec3 const screen = mCoordChange.WorldToScreen(posW);
		glPushMatrix();
		glTranslatef(screen.x, screen.y, 0);
		mText.drawAlternative(Vec3(0, 0), Vec3(1, 1), Vec3(0, 0), Vec3(w, h));
		glPopMatrix();
		mProjectiles[0]->Draw(t,dt); mProjectiles[1]->Draw(t,dt); mProjectiles[2]->Draw(t,dt);
	}
}

