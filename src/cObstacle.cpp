#include "cScene.hpp"
#include "Globals.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

cObstacle::cObstacle(cScene const& map) : cBicho(map) {
}
bool cObstacle::Init() {
	return mText.Load(mFilename.c_str(), GL_RGBA);
}
void cObstacle::Draw() const {
	float screen_x, screen_y;
	std::tie(screen_x, screen_y) = mMap.WorldToScreen(xW,yW);
	mText.Draw(0,0,1,1,  screen_x, screen_y, screen_x+w, screen_y+h);
}