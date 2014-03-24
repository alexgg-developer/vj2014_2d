#include "cPlayer.hpp"

cPlayer::cPlayer(cScene const& map, cCoordChanges const& ch) : cBicho(map, ch) {}
cPlayer::~cPlayer(){}

void cPlayer::Draw() {
	float xo,yo;

	switch(GetState()) {
		//1
		case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.25f;
								break;
		//4
		case STATE_LOOKRIGHT:	xo = 0.25f;	yo = 0.25f;
								break;
		//1..3
		case STATE_WALKLEFT:	xo = 0.0f;	yo = 0.25f + (GetFrame()*0.25f);
								NextFrame(3);
								break;
		//4..6
		case STATE_WALKRIGHT:	xo = 0.25f; yo = 0.25f + (GetFrame()*0.25f);
								NextFrame(3);
								break;
	}
	Vec3 const texf(xo + 0.25f, yo - 0.25f);

	DrawRect(Vec3(xo,yo), texf, mCoordChange.WorldToScreen(posW));
}
bool cPlayer::Init() {
	return mText.Load("bub.png",GL_RGBA); }
