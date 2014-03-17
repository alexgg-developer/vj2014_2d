#pragma once
#include "cBicho.hpp"
#include "cTexture.hpp"

struct cPlayer: public cBicho {
	cPlayer(unsigned int const aTileSize);
	~cPlayer();

	bool Init();
	void Draw(int sceneOriginX, int sceneOriginY, int blocksize);
protected:
	cTexture mText;
};
