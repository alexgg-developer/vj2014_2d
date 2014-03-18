#pragma once
#include "cBicho.hpp"
#include "cScene.hpp"

struct cPlayer: public cBicho {
	cPlayer(cScene const& map);
	~cPlayer();

	bool Init();
	//TODO Draw modifies the object. Oh shit. kill kill kill kill kill kill kill kill kill kill ikill oh, that may be a new apple product kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
	void Draw();
};
