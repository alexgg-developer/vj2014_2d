#pragma once
#include "cScene.hpp"
#include "cPlayer.hpp"
#include "cEnemy.hpp"
#include "cNormalShip.hpp"
#include "cWalkingBomb.hpp"
#include "cCoordChanges.hpp"
#include "cExplosion.hpp"

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
	void ReadKeyboardEspecial(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process(float dt);
	//Output
	void Render();

  void addExplosion(cExplosion expl) { mExplosions.push_back(expl); }

protected:
	//unsigned char keys[256];
	enum keysDefined { KUP, KDOWN, KRIGHT, KLEFT, KQ, KW, KE, KA, KS, KD, KESC, KSPACE, NUMKEYS };
	enum keyStatus{ KEY_OFF, KEY_ON, KEY_RELEASED, KEY_PRESSED };
	unsigned int mKey[NUMKEYS];	
	cScene Scene;
	cPlayer Player;
  cCoordChanges CoordChanges;
	std::vector<cEnemy*> mEnemies;
  std::vector<cExplosion> mExplosions;
};
