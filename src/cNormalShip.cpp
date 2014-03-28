#include "cNormalShip.hpp"


cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch, bool awake) : cEnemy(map, ch)
{
	w = 64; h = 64;
	mAwake = awake;
	if (!mText.Load("enemy1.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	mPhysics = std::make_shared<cPhysics>(Vec3(-100.0f, 0), Vec3(-100.0f, 0), Vec3(-50.0f, 0));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(map, ch));
}


cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch, int life, bool awake) : cEnemy(map, ch, life)
{
	w = 64; h = 64;
	mAwake = awake;
	if (!mText.Load("enemy1.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	mPhysics = std::make_shared<cPhysics>(Vec3(-100.0f, 0), Vec3(-100.0f, 0), Vec3(-50.0f, 0));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(map, ch));
}
#include <iostream>
cNormalShip::cNormalShip(cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake) 
: cEnemy(map, ch, life)
{
	w = 64; h = 64;
	setInitialTilePosition(tilePosition);
	mAwake = awake;
	if (!mText.Load("enemy1.png", GL_RGBA)) {
		std::cerr << "Texture did not load" << std::endl;
	}
	mPhysics = std::make_shared<cPhysics>(Vec3(-100.0f, 0), Vec3(-100.0f, 0), Vec3(-50.0f, 0));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(map, ch));
	mProjectiles.push_back(std::make_shared<cNormalProjectile>(map, ch));
}

void cNormalShip::doLogic(float dt)
{
	if (mAwake) {
		if (!mProjectiles[0]->mAwake) {
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
		mProjectiles[0]->doLogic(dt); mProjectiles[1]->doLogic(dt); mProjectiles[2]->doLogic(dt);
	}
}


void cNormalShip::draw()
{
	if (mAwake) {
		Vec3 const screen = mCoordChange.WorldToScreen(posW);
		glPushMatrix();
		glTranslatef(screen.x, screen.y, 0);
		mText.drawAlternative(Vec3(0, 0), Vec3(1, 1), Vec3(0, 0), Vec3(w, h));
		glPopMatrix();
		mProjectiles[0]->draw(); mProjectiles[1]->draw(); mProjectiles[2]->draw();

	}
}

