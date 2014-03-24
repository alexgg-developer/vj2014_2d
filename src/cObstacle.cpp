#include "cScene.hpp"
#include "Globals.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

cObstacle::cObstacle(cScene const& map, cCoordChanges const& ch) : cBicho(map, ch) {
}
bool cObstacle::Init() {
	return mText.Load(mFilename.c_str(), GL_RGBA);
}
void cObstacle::Draw() const {
	Vec3 const screen = mCoordChange.WorldToScreen(posW);
	mText.Draw(Vec3(0,0), Vec3(1,1),  screen, Vec3(screen.x+w, screen.y+h));
}
