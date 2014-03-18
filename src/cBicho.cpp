#include "cBicho.hpp"
#include "cScene.hpp"
#include "Globals.hpp"

#define FRAME_DELAY		8
#define STEP_LENGTH		2
#define JUMP_HEIGHT		96
#define JUMP_STEP		4

cBicho::cBicho(unsigned int const aTileSize) : mTileSize(aTileSize) {
	seq=0;
	delay=0;

	jumping = false;
}
cBicho::~cBicho(void){}

cBicho::cBicho(unsigned int const aTileSize, int posx,int posy,int width,int height) : mTileSize(aTileSize) {
	x = posx;
	y = posy;
	w = width;
	h = height;
}
void cBicho::SetPosition(int posx,int posy) {
	x = posx;
	y = posy;
}

std::tuple<int,int> cBicho::GetPosition() const {
	return std::make_tuple(x,y); }
void cBicho::SetTile(int tx,int ty) {
	x = tx * mTileSize;
	y = ty * mTileSize;
}

std::tuple<int,int> cBicho::GetTile() const {
	return std::make_tuple(x / mTileSize, y / mTileSize); }
void cBicho::SetWidthHeight(int width,int height) {
	w = width;
	h = height; }

std::tuple<int, int> cBicho::GetWidthHeight() const {
	return std::make_tuple(w,h); }

bool cBicho::Collides(cRect const& rc) const {
	return ((x>rc.left) && (x+w<rc.right) && (y>rc.bottom) && (y+h<rc.top));
}
bool cBicho::CollidesMapWall(cScene const& map,bool right) const {
	int tile_x = x / mTileSize;
	int const tile_y = y / mTileSize;
	int const width_tiles  = w / mTileSize;
	int const height_tiles = h / mTileSize;

	if(right) tile_x += width_tiles;
	
	for(int j=0;j<height_tiles;j++)	{
		if(map(tile_x, (tile_y+j)) != 0)	return true;
	}
	
	return false;
}

bool cBicho::CollidesMapFloor(cScene const& map) {
	int const tile_x = x / mTileSize;
	int const tile_y = y / mTileSize;

	int width_tiles = w / mTileSize;
	if( (x % mTileSize) != 0) width_tiles++;

	bool on_base = false;
	int i=0;
	while((i<width_tiles) && !on_base) {
		if( (y % mTileSize) == 0 ) {
			if(map((tile_x + i), (tile_y - 1)) != 0)
				on_base = true;
		}
		else {
			if(map((tile_x + i), tile_y) != 0) {
				y = (tile_y + 1) * mTileSize;
				on_base = true;
			}
		}
		i++;
	}
	return on_base;
}

cRect cBicho::GetArea() const {
	cRect rc;
	rc.left   = x;
	rc.right  = x+w;
	rc.bottom = y;
	rc.top    = y+h;
	return rc;
}
void cBicho::DrawRect(float const xo,float const yo,float const xf,float const yf,
					  float const screen_x, float const screen_y) const {
	mText.Draw(xo, yo, xf, yf, screen_x, screen_y, screen_x+w, screen_y+h);
}

void cBicho::MoveLeft(cScene const& map) {
	//Whats next tile?
	if( (x % mTileSize) == 0) {
		int xaux = x;
		x -= STEP_LENGTH;

		if(CollidesMapWall(map,false)) {
			x = xaux;
			state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else {
		x -= STEP_LENGTH;
		if(state != STATE_WALKLEFT) {
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveRight(cScene const& map) {
	//Whats next tile?
	if( (x % mTileSize) == 0) {
		int xaux;
		xaux = x;
		x += STEP_LENGTH;

		if(CollidesMapWall(map,true)) {
			x = xaux;
			state = STATE_LOOKRIGHT;
		}
	}
	//Advance, no problem
	else {
		x += STEP_LENGTH;

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
void cBicho::Jump(cScene const& map) {
	if(!jumping) {
		if(CollidesMapFloor(map)) {
			jumping = true;
			jump_alfa = 0;
			jump_y = y;
		}
	}
}
void cBicho::Logic(cScene const& map) {
	if(jumping)	{
		jump_alfa += JUMP_STEP;
		
		if(jump_alfa == 180) {
			jumping = false;
			y = jump_y;
		}
		else {
			float alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)( ((float)JUMP_HEIGHT) * sin(alfa) );
		
			if(jump_alfa > 90) {
				//Over floor?
				jumping = !CollidesMapFloor(map);
			}
		}
	}
	else {
		//Over floor?
		if(!CollidesMapFloor(map))
			y -= (2*STEP_LENGTH);
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