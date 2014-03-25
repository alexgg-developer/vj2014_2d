#pragma once
#include "cScene.hpp"
#include "cPlayer.hpp"
#include "cEnemy.hpp"
#include "cNormalShip.hpp"
#include "cCoordChanges.hpp"

#include <vector>

#define GAME_WIDTH	640
#define GAME_HEIGHT 480

struct cGame {
	cGame();
	virtual ~cGame();

	bool Init();
	bool Loop(float dt);
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process(float dt);
	//Output
	void Render();

protected:
	unsigned char keys[256];
	cScene Scene;
	cPlayer Player;
   cCoordChanges CoordChanges;
	std::vector<cEnemy*> mEnemies;
};
