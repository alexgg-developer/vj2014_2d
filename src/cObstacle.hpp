#pragma once
#include <string>
#include "cBicho.hpp"

struct cObstacle : public cBicho {
  cObstacle(cScene const& map, cCoordChanges const& ch);
	bool Init();
	void Draw() const;

	friend std::istream& operator>>(std::istream& is, cObstacle& obs) {
	  int mPosX, mPosY;
	  is >> obs.mFilename >> mPosX >> mPosY;
      obs.SetTile(mPosX,mPosY);	
	  return is;
	}

  protected:
	std::string mFilename;
};
