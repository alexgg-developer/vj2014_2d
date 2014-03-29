#include "cGame.hpp"
#include "Globals.hpp"


cGame::cGame(void) : CoordChanges(), Scene(CoordChanges, Player), Player(Scene, CoordChanges)
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
	Scene.Init();
	if(!Scene.LoadLevel(4)) return false;

	//Player initialization
	Player.Init();
	Player.SetWidthHeight_W(40,40);
	Player.SetPosition_T(Vec3(2,1)); //Initial tile

	//Enemy initialization
	//mEnemies.push_back(new cNormalShip(Scene, CoordChanges, 1, Vec3(15, 17), true));
	mEnemies.push_back(new cNormalShip(Scene, CoordChanges, 1, Vec3(22, 22), true));
	mEnemies.push_back(new cWalkingBomb(Scene, CoordChanges, 1, Vec3(35, 1), true, Player));
	

  cExplosion::initialize(this);

	return true;
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
	if (mKey[KSPACE] == KEY_PRESSED || mKey[KSPACE] == KEY_ON) {
		Player.Jump();
	}
	if (mKey[KUP] == KEY_PRESSED || mKey[KUP] == KEY_ON) {
		direction.y = 1.0;
		//Player.Jump();
	}
	if (mKey[KDOWN] == KEY_PRESSED || mKey[KDOWN] == KEY_ON) {
		direction.y = -1.0;
	}

	if (mKey[KLEFT] == KEY_PRESSED || mKey[KLEFT] == KEY_ON) {
		Player.MoveLeft();
		direction.x = -1.0;
	}
	else if (mKey[KRIGHT] == KEY_PRESSED || mKey[KRIGHT] == KEY_ON)	{
		Player.MoveRight();
		direction.x = 1.0;
	}
	else Player.Stop();

	if (mKey[KQ] == KEY_PRESSED) {
		mKey[KQ] = KEY_ON; //This is because process is more called than keyboard
		Player.Attack(direction, cElementalProjectile::FIRE);
	}
	if (mKey[KW] == KEY_PRESSED) {
		mKey[KW] = KEY_ON;
		Player.Attack(direction, cElementalProjectile::ICE);
	}
	if (mKey[KE] == KEY_PRESSED) {
		mKey[KE] = KEY_ON;
		Player.Attack(direction, cElementalProjectile::ELECTRIC);
	}

	//Game Logic
	Player.doLogic(t,dt);
	for (std::size_t i = 0; i < mEnemies.size(); ++i) mEnemies[i]->doLogic(t,dt);
  for(std::vector<cExplosion>::iterator it = mExplosions.begin(); it!=mExplosions.end();) {
    if (it->hasFinished(t))
      it = mExplosions.erase(it);
    else it++;
  }
  Scene.doLogic(t,dt);

	return res;
}

//Output
void cGame::Render(float const t, float const dt) {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();

	glPushMatrix();
	Scene.Draw(t,dt);
	Player.Draw(t,dt);
	
	for (size_t i = 0; i < mEnemies.size(); ++i) {
		mEnemies[i]->Draw(t,dt);
	}
  for(auto& expl: mExplosions)
    expl.Draw(t,dt);
	glutSwapBuffers();
}
