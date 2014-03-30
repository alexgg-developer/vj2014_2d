#include "cGame.hpp"
#include "Globals.hpp"
#include <memory>

cGame::cGame(void) : Scene(new cMenu(this))
{ 
	for (unsigned int i = 0; i < NUMKEYS; ++i) mKey[i] = KEY_OFF;

}

cGame::~cGame(void) { }

bool cGame::Init() {
	//Graphics initialization
	glClearColor(0.5f,0.5f,0.5f,1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	Scene->Init();
	return Scene->LoadLevel(4);
}

bool cGame::Loop(float const t, float const dt) {
	bool res = Process(t, dt);
	if(res) Render(t,dt);

	return res;
}

void cGame::Finalize() {
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	
	for (unsigned int i = KQ; i < NUMKEYS; ++i) mKey[i] = mKey[i] & 0x0001;

	if (press) {
		switch (key) {
		case 'q':
			if (mKey[KQ] != KEY_ON) {
				mKey[KQ] = KEY_PRESSED;
			}
			break;
		case 'w':
			if (mKey[KW] != KEY_ON) {
				mKey[KW] = KEY_PRESSED;
			}
			break;
		case 'e':
			if (mKey[KE] != KEY_ON) {
				mKey[KE] = KEY_PRESSED;
			}
			break;

		case 's':
			if (mKey[KS] != KEY_ON) {
				mKey[KS] = KEY_PRESSED;
			}
			break;

		case ' ':
			if (mKey[KSPACE] != KEY_ON) {
				mKey[KSPACE] = KEY_PRESSED;
			}
			break;
		case 27: //SCAPE
			if (mKey[KESC] != KEY_ON) {
				mKey[KESC] = KEY_PRESSED;
			}
			break;
		}
	}
	else {
		//I'll do key_off directly because we dont need if it's been recently released. So we can avoid a verification
		switch (key) {
		case 'q':
			mKey[KQ] = KEY_OFF;
			break;
		case 'w':
			mKey[KW] = KEY_OFF;
			break;
		case 'e':
			mKey[KE] = KEY_OFF;
			break;
		case 's':
			mKey[KS] = KEY_OFF;
			break;
		case ' ':
			mKey[KSPACE] = KEY_OFF;
			break;
		}
	}
}

void cGame::ReadKeyboardEspecial(unsigned char key, int x, int y, bool press) 
{
	for (unsigned int i = 0; i < KQ; ++i) mKey[i] = mKey[i] & 0x0001;
	if (press) {
		switch (key) {
		case GLUT_KEY_LEFT:
			if (mKey[KLEFT] != KEY_ON) {
				mKey[KLEFT] = KEY_PRESSED;
			}
			break;
		case GLUT_KEY_RIGHT:
			if (mKey[KRIGHT] != KEY_ON) {
				mKey[KRIGHT] = KEY_PRESSED;
			}
			break;
		case GLUT_KEY_UP:
			if (mKey[KUP] != KEY_ON) {
				mKey[KUP] = KEY_PRESSED;
			}
			break;

		case GLUT_KEY_DOWN:
			if (mKey[KDOWN] != KEY_ON) {
				mKey[KDOWN] = KEY_PRESSED;
			}
			break;
		}
	}
	else {
		//I'll do key_off directly because we dont need if it's been recently released. So we can avoid a verification
		switch (key) {
		case GLUT_KEY_LEFT:
			mKey[KLEFT] = KEY_OFF;
			break;
		case GLUT_KEY_RIGHT:
			mKey[KRIGHT] = KEY_OFF;
			break;
		case GLUT_KEY_UP:
			mKey[KUP] = KEY_OFF;
			break;
		case GLUT_KEY_DOWN:
			mKey[KDOWN] = KEY_OFF;
			break;
		}
	}

}

void cGame::ReadMouse(int button, int state, int x, int y) {
}

//Process
bool cGame::Process(float const t, float const dt) {
	bool res=true;
	
	//Process Input
	Vec3 direction = Vec3(0, 0, 0);

	if (mKey[KESC] == KEY_PRESSED) {
		res = false;
	}
	if (mKey[KS] == KEY_PRESSED || mKey[KS] == KEY_ON) {
    if(Scene->AvoidRepetitionsS()) {
	    if (mKey[KS] == KEY_PRESSED) {
		    mKey[KS] = KEY_ON; //This is because process is more called than keyboard
        Scene->UpKey();
      }
    } else 
        Scene->UpKey();
	}
	if (mKey[KSPACE] == KEY_PRESSED || mKey[KSPACE] == KEY_ON) {
		Scene->PressedEnter();
	}
	if (mKey[KUP] == KEY_PRESSED || mKey[KUP] == KEY_ON) {
		direction.y = 1.0;
		//Player.Jump();
	}
	if (mKey[KDOWN] == KEY_PRESSED || mKey[KDOWN] == KEY_ON) {
		direction.y = -1.0;
	}

	if (mKey[KLEFT] == KEY_PRESSED || mKey[KLEFT] == KEY_ON) {
		Scene->LeftKey();
		direction.x = -1.0;
	}
	else if (mKey[KRIGHT] == KEY_PRESSED || mKey[KRIGHT] == KEY_ON)	{
		Scene->RightKey();
		direction.x = 1.0;
	}
	else Scene->Stop();

	if (mKey[KQ] == KEY_PRESSED) {
		mKey[KQ] = KEY_ON; //This is because process is called more often than keyboard
		Scene->Attack(direction, cElementalProjectile::FIRE);
	}
	if (mKey[KW] == KEY_PRESSED) {
		mKey[KW] = KEY_ON;
		Scene->Attack(direction, cElementalProjectile::ICE);
	}
	if (mKey[KE] == KEY_PRESSED) {
		mKey[KE] = KEY_ON;
		Scene->Attack(direction, cElementalProjectile::ELECTRIC);
	}

	//Game Logic
  Scene->doLogic(t,dt);

	return res;
}

//Output
void cGame::Render(float const t, float const dt) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	Scene->Draw(t,dt);
	glutSwapBuffers();
}

void cGame::changeLevel(iScene* s) {
  Scene = std::shared_ptr<iScene>(s);
}