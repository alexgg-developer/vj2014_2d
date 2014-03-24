#include "cBicho.hpp"
#include "cScene.hpp"
#include "Globals.hpp"

#define FRAME_DELAY		8
#define STEP_LENGTH		4
#define JUMP_HEIGHT		96
#define JUMP_STEP		4

cBicho::cBicho(cScene const& map, cCoordChanges const& ch) : mMap(map), mCoordChange(ch), delay(0), seq(0), jumping(false) {}
cBicho::~cBicho(void){}

cBicho::cBicho(cScene const& map, cCoordChanges const& ch, int posxW,int posyW,int width,int height) : mMap(map), mCoordChange(ch) {
	posW.x = posxW;
	posW.y = posyW;
	w = width;
	h = height;
}
void cBicho::SetPosition_W(Vec3 apos) {
	posW = apos;
}

Vec3 cBicho::GetPosition_W() const {
	return posW; }
void cBicho::SetPosition_T(Vec3 tile) {
	 posW = mCoordChange.TileToWorld(tile);
}

Vec3 cBicho::GetPosition_T() const {
	return mCoordChange.WorldToTile(posW); }
void cBicho::SetWidthHeight_W(int width,int height) {
	w = width;
	h = height; }

int cBicho::GetWidth_W() const { return w;}
int cBicho::GetHeight_W() const{ return h;}
bool cBicho::Collides_W(cRect const& rcW) const {
	return !((posW.x > rcW.right) || (rcW.left > (posW.x+w)) || (posW.y > rcW.top) || (rcW.bottom > (posW.y+h)));
}
bool cBicho::CollidesMapWall(bool right) const {
	Vec3 posW2 = posW;
	int const w2  = w;

	if(right) posW2.x += w2;
	
	bool collides = mMap.CollisionInClosedArea(posW2, Vec3(posW2.x, posW2.y+h-1));
	return collides;
}

bool cBicho::CollidesMapFloor() const {
	int w2 = w;
	if( (int(posW.x) % mCoordChange.GetTileSize()) != 0) w2++;

	bool on_base = false;
	if( (int(posW.y) % mCoordChange.GetTileSize()) == 0 )
		on_base = mMap.CollisionInClosedArea(Vec3(posW.x, posW.y-1), Vec3(posW.x+w2-1, posW.y-1));
	else {
		on_base = mMap.CollisionInClosedArea(Vec3(posW.x, posW.y  ), Vec3(posW.x+w2-1, posW.y  ));
	}

	return on_base;
}

cRect cBicho::GetArea_W() const {
	return cRect(posW.x, posW.x+w, posW.y, posW.y+h);
}
void cBicho::DrawRect(Vec3 const& tex0, Vec3 const& tex1,
					  Vec3 const& screen) const {
	mText.Draw(tex0, tex1, screen, Vec3(screen.x+w, screen.y+h));
}

void cBicho::MoveLeft() {
	//Whats next tile?
	if( (int(posW.x) % mCoordChange.GetTileSize()) == 0) {
		int xaux = posW.x;
		posW.x -= STEP_LENGTH;

		if(CollidesMapWall(false)) {
			posW.x = xaux;
			state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else {
		posW.x -= STEP_LENGTH;
		if(state != STATE_WALKLEFT) {
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveRight() {
	//Whats next tile?
	if( (int(posW.x) % mCoordChange.GetTileSize()) == 0) {
		int xaux;
		xaux = posW.x;
		posW.x += STEP_LENGTH;

		if(CollidesMapWall(true)) {
			posW.x = xaux;
			state = STATE_LOOKRIGHT;
		}
	}
	//Advance, no problem
	else {
		posW.x += STEP_LENGTH;

		if(state != STATE_WALKRIGHT) {
			state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}
}

void cBicho::Stop() {
	switch(state) {
		case STATE_WALKLEFT:	state = STATE_LOOKLEFT;		break;
		case STATE_WALKRIGHT:	state = STATE_LOOKRIGHT;	break;
	}
}
void cBicho::Jump() {
	if(!jumping) {
		if(CollidesMapFloor()) {
			jumping = true;
			jump_alfa = 0;
			jump_y = posW.y;
		}
	}
}
#include <iostream>
void cBicho::Logic() {
	if(jumping)	{
		jump_alfa += JUMP_STEP;
		
		if(jump_alfa == 180) {
			jumping = false;
			posW.y = jump_y;
		}
		else {
			/// I really love magic constants. I love them until I puke.
			float alfa = ((float)jump_alfa) * 0.017453f;
			float oldy = posW.y;
			posW.y = jump_y + ( float(JUMP_HEIGHT) * sin(alfa) );
		
			if(jump_alfa > 90) {
				//Over floor?
				jumping = !CollidesMapFloor();
				// Colócalo en el suelo, motherfucker
				if(!jumping) {
					int const w2 = w;
					//if( (int(posW.x) % mCoordChange.GetTileSize()) != 0) w2++;//No sé que hace. Estaba en el código original.
					while(mMap.CollisionInClosedArea(Vec3(posW.x, posW.y  ), Vec3(posW.x+w2-1, posW.y  ))) {
						posW.y +=1;
					}
				}
			}
		}
	}
	else {
		//Caída libre muy cutre
		if(!CollidesMapFloor())
			posW.y -= (STEP_LENGTH);
	}
}
void cBicho::NextFrame(int max) {
	delay++;
	if(delay == FRAME_DELAY) {
		seq++;
		seq%=max;
		delay = 0;
	}
}

int cBicho::GetFrame() const {
	return seq; }
BichoState cBicho::GetState() const {
	return state; }
void cBicho::SetState(BichoState s) {
	state = s;
}
