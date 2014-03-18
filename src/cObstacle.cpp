#include "cScene.hpp"
#include "Globals.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

cObstacle::cObstacle(unsigned int const aTileSize) : cBicho(aTileSize) {
}
bool cObstacle::Init() {
	return mText.Load(mFilename.c_str(), GL_RGBA);
}
void cObstacle::Draw(int const sceneOriginX, int const sceneOriginY, int const blocksize) const {
	float const screen_x = x + sceneOriginX;
	float const screen_y = y + sceneOriginY + (blocksize - mTileSize);
	mText.Draw(0,0,1,1,  screen_x, screen_y, screen_x+w, screen_y+h);
}