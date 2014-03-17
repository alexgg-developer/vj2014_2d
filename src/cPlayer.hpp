#pragma once

#include "cBicho.hpp"
#include "cTexture.hpp"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

struct cPlayer: public cBicho {
	cPlayer();
	~cPlayer();

	bool Init();
	void Draw();
protected:
	cTexture mText;
};
