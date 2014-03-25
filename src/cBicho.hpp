#pragma once
#include "cTexture.hpp"
#include "cCoordChanges.hpp"
#include "Vec3.hpp"
#include "cAni.hpp"
#include <array>
#include <memory>
struct cState;
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
  cBicho(cScene const& map, cCoordChanges const& ch);
  cBicho(cScene const& map, cCoordChanges const& ch, int x,int y,int w,int h);
  ~cBicho();

  void SetPosition_W(Vec3 apos);
  Vec3 GetPosition_W() const; //TODO: Which position? Which coordinate system?
  void SetPosition_T(Vec3 tile);
  Vec3 GetPosition_T() const;
  void SetWidthHeight_W(int w,int h);
  int GetWidth_W() const;
  int GetHeight_W() const;

  bool Collides_W(cRect const& rcW) const;
  bool CollidesMapWall(bool right) const;
  bool CollidesMapFloor() const;
  cRect GetArea_W() const;
  void DrawRect(cFrame const& fr,
				Vec3 const& screen) const;

  void MoveRight();
  void MoveLeft();
  void Jump();
  void Stop();
  void Logic();

  cState* GetState() const;
  void SetState(cState* s);

  cBicho& operator=(cBicho const& other) {
    mText=other.mText;
    posW.x=other.posW.x;
    posW.y=other.posW.y;
    w = other.w;
    h = other.h;
    mActualState = other.mActualState;
    mStates = other.mStates;
    jumping = other.jumping;
    jump_alfa = other.jump_alfa;
    jump_y = other.jump_y;
    return *this;
  }
	
protected:
  cScene const& mMap;
  cCoordChanges const& mCoordChange;
  cTexture mText;
  Vec3 posW;
  int w,h;

  bool jumping;
  int jump_alfa;
  int jump_y;
  cState* mActualState;
  std::array<std::shared_ptr<cState>, 4> mStates;
private:
  void initStates();
};
