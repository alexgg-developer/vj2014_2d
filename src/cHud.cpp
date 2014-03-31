#include "cScene.hpp"
#include "Globals.hpp"
#include "cHud.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

cHud::cHud(cScene const& map, cCoordChanges const& ch) : cBicho(map, ch), mLife(0) {
}
bool cHud::Init() {

	bool heartLoaded = mHeartFull.Load("heart_full_16x16.png", GL_RGBA);
	bool heartEmptyLoaded = mHeartEmpty.Load("heart_empty_16x16.png", GL_RGBA);

	return heartLoaded && heartEmptyLoaded;
}
void cHud::update(int life)
{
	mLife = life;
}

void cHud::Draw(float const t, float const dt) const {
	Vec3 const screen = mCoordChange.WorldToScreen(posW);
	int padding = 40;
	for (size_t i = 0; i < mLife; ++i) {
		mHeartFull.drawAlternative(Vec3(0, 0), Vec3(1, 1), screen + Vec3(i * padding, 0), Vec3(screen.x + mHeartWidth + i * padding, screen.y + mHeartHeight));
	}
	for (size_t i = mLife; i < 3; ++i) {
		mHeartEmpty.drawAlternative(Vec3(0, 0), Vec3(1, 1), screen + Vec3(i * padding, 0), Vec3(screen.x + mHeartWidth + i * padding, screen.y + mHeartHeight));
	}
}
