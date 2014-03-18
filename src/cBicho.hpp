#pragma once
#include "Globals.hpp"
#include "cTexture.hpp"
#include <tuple>
struct cScene;

enum BichoState {
 STATE_LOOKLEFT  =0,
 STATE_LOOKRIGHT =1,
 STATE_WALKLEFT  =2,
 STATE_WALKRIGHT =3};

struct cRect {
	cRect(int const l, int const r, int const b, int const t) : left(l), right(r), top(t), bottom(b) {}
	int left,top,
		right,bottom;
};

struct cBicho {
	cBicho(cScene const& map);
	cBicho(cScene const& map, int x,int y,int w,int h);
	~cBicho();

	void SetPosition(int xW,int yW);
	std::tuple<int,int> GetPosition() const;
	void SetTile(int tx,int ty);
	std::tuple<int,int> GetTile() const;
	void SetWidthHeight(int w,int h);
	std::tuple<int, int> GetWidthHeight() const;

	bool Collides(cRect const& rcW) const;
	bool CollidesMapWall(bool right) const;
	///TODO This function modifies the object. It's not a query, be careful!
	bool CollidesMapFloor();
	cRect GetArea() const;
	void DrawRect(float xo,float yo,float xf,float yf,
				  float const screen_x, float const screen_y) const;

	void MoveRight();
	void MoveLeft();
	void Jump();
	void Stop();
	void Logic();

	BichoState GetState() const;
	void SetState(BichoState s);

	void NextFrame(int max);
	int  GetFrame() const;

	cBicho& operator=(cBicho const& other) {
		mText=other.mText;
		xW=other.xW;
		yW=other.yW;
		w = other.w;
		h = other.h;
		state = other.state;
		jumping = other.jumping;
		jump_alfa = other.jump_alfa;
		jump_y = other.jump_y;
		seq = other.seq;
		delay = other.delay;
		return *this;
	}
	
protected:
	cScene const& mMap;
	cTexture mText;
	int xW,yW;
	int w,h;
	BichoState state;

	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq,delay;
};
