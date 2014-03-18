#include "cPlayer.hpp"

cPlayer::cPlayer(cScene const& map) : cBicho(map) {}
cPlayer::~cPlayer(){}

void cPlayer::Draw() {
	float xo,yo,xf,yf;

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
	xf = xo + 0.25f;
	yf = yo - 0.25f;
	float screen_x, screen_y;
	std::tie(screen_x, screen_y) = mMap.WorldToScreen(xW,yW);

	DrawRect(xo,yo,xf,yf, screen_x, screen_y);
}
bool cPlayer::Init() {
	return mText.Load("bub.png",GL_RGBA); }