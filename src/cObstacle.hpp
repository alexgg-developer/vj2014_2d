#pragma once
#include <vector>
#include <string>
#include "cBicho.hpp"

struct cObstacle : public cBicho {
	cObstacle(unsigned int const aTileSize);
	bool Init();
	void Draw(int const sceneOriginX, int const sceneOriginY, int const blocksize) const;

	friend std::istream& operator>>(std::istream& is, cObstacle& obs) {
	  int mPosX, mPosY;
	  is >> obs.mFilename >> mPosX >> mPosY;
      obs.SetTile(mPosX,mPosY);	
	  return is;
	}
  protected:
	std::string mFilename;
};