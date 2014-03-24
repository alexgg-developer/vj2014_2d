#include "cBicho.hpp"
#include "cScene.hpp"
#include "Globals.hpp"

#define FRAME_DELAY		8
#define STEP_LENGTH		2
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
void cBicho::SetTile(Vec3 tile) {
	 posW = mCoordChange.TileToWorld(tile);
}

Vec3 cBicho::GetTile() const {
	return mCoordChange.WorldToTile(posW); }
void cBicho::SetWidthHeight(int width,int height) {
	w = width;
	h = height; }

std::tuple<int, int> cBicho::GetWidthHeight() const {
	return std::make_tuple(w,h); }

bool cBicho::Collides(cRect const& rcW) const {
	return ((posW.x>rcW.left) && (posW.x+w<rcW.right) && (posW.y>rcW.bottom) && (posW.y+h<rcW.top));
}
bool cBicho::CollidesMapWall(bool right) const {
	Vec3 tile = mCoordChange.WorldToTile(posW);
	int const width_tiles  = w / mCoordChange.getTileSize();
	int const height_tiles = h / mCoordChange.getTileSize();

	if(right) tile.x += width_tiles;
	
	bool collides = mMap.CollisionInClosedArea(tile.x, tile.x, tile.y, tile.y+height_tiles-1);
	return collides;
}

bool cBicho::CollidesMapFloor() {
	Vec3 const tile = mCoordChange.WorldToTile(posW);

	int width_tiles = w / mCoordChange.getTileSize();
	if( (int(posW.x) % mCoordChange.getTileSize()) != 0) width_tiles++;

	bool on_base = false;
	if( (int(posW.y) % mCoordChange.getTileSize()) == 0 )
		on_base = mMap.CollisionInClosedArea(tile.x, tile.x+width_tiles-1, tile.y-1, tile.y-1);
	else {
		on_base = mMap.CollisionInClosedArea(tile.x, tile.x+width_tiles-1, tile.y, tile.y);
		if(on_base)
		  posW.y = (tile.y + 1) * mCoordChange.getTileSize();
	}

	return on_base;
}

cRect cBicho::GetArea() const {
	return cRect(posW.x, posW.x+w, posW.y, posW.y+h);
}
void cBicho::DrawRect(float const xo,float const yo,float const xf,float const yf,
					  float const screen_x, float const screen_y) const {
	mText.Draw(xo, yo, xf, yf, screen_x, screen_y, screen_x+w, screen_y+h);
}

void cBicho::MoveLeft() {
	//Whats next tile?
	if( (int(posW.x) % mCoordChange.getTileSize()) == 0) {
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
	if( (int(posW.x) % mCoordChange.getTileSize()) == 0) {
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
			posW.y = jump_y + (int)( ((float)JUMP_HEIGHT) * sin(alfa) );
		
			if(jump_alfa > 90) {
				//Over floor?
				jumping = !CollidesMapFloor();
			}
		}
	}
	else {
		//Over floor?
		if(!CollidesMapFloor())
			posW.y -= (2*STEP_LENGTH);
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
