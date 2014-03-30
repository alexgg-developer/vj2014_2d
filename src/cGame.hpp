#pragma once
#include "cScene.hpp"
#include "cExplosion.hpp"

#include <vector>

#define GAME_WIDTH	640
#define GAME_HEIGHT 480

struct cGame {
	cGame();
	virtual ~cGame();

	bool Init();
	bool Loop(float const t, float const dt);
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadKeyboardEspecial(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process(float const t, float const dt);
	//Output
	void Render(float const t, float const dt);

  void changeLevel(iScene* s);

protected:
	enum keysDefined { KUP, KDOWN, KRIGHT, KLEFT, KQ, KW, KE, KA, KS, KD, KESC, KSPACE, NUMKEYS };
	enum keyStatus{ KEY_OFF, KEY_ON, KEY_RELEASED, KEY_PRESSED };
	unsigned int mKey[NUMKEYS];	
	std::shared_ptr<iScene> Scene;
};
