#pragma once
#include <string>
#include "cBicho.hpp"

struct cObstacle : public cBicho {
  cObstacle(cScene const& map, cCoordChanges const& ch);
	bool Init();
	virtual void Draw(float const t, float const dt) const override;
	virtual void doLogic(float const t, float const dt) override {} //TODO Make it destructable

	friend std::istream& operator>>(std::istream& is, cObstacle& obs) {
	  int mPosX, mPosY;
	  is >> obs.mFilename >> mPosX >> mPosY;
      obs.SetPosition_T(Vec3(mPosX,mPosY));	
	  return is;
	}

  protected:
	std::string mFilename;
};
