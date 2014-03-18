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
	int left,top,
		right,bottom;
};

struct cBicho {
	cBicho(unsigned int const aTileSize);
	cBicho(unsigned int const aTileSize, int x,int y,int w,int h);
	~cBicho();

	void SetPosition(int x,int y);
	std::tuple<int,int> GetPosition() const;
	void SetTile(int tx,int ty);
	std::tuple<int,int> GetTile() const;
	void SetWidthHeight(int w,int h);
	std::tuple<int, int> GetWidthHeight() const;

	bool Collides(cRect const& rc) const;
	bool CollidesMapWall(cScene const& map, bool right) const;
	///TODO This function modifies the object. It's not a query, be careful!
	bool CollidesMapFloor(cScene const& map);
	cRect GetArea() const;
	void DrawRect(float xo,float yo,float xf,float yf,
				  float const screen_x, float const screen_y) const;

	void MoveRight(cScene const& map);
	void MoveLeft(cScene const& map);
	void Jump(cScene const& map);
	void Stop();
	void Logic(cScene const& map);

	BichoState GetState() const;
	void SetState(BichoState s);

	void NextFrame(int max);
	int  GetFrame() const;
	
protected:
	cTexture mText;
	unsigned int mTileSize; //TODO: WTF?
	int x,y;
	int w,h;
	BichoState state;

	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq,delay;
};
