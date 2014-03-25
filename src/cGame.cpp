#include "cGame.hpp"
#include "Globals.hpp"


cGame::cGame(void) : CoordChanges(), Scene(CoordChanges), Player(Scene, CoordChanges) { }

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
	if(!Scene.LoadLevel(1)) return false;

	//Player initialization
	Player.Init();
	Player.SetWidthHeight_W(32,32);
	Player.SetPosition_T(Vec3(2,1)); //Initial tile

	//Enemy initialization
	mEnemies.push_back(new cNormalShip(Scene, CoordChanges, 1, Vec3(15, 17)));
	mEnemies.push_back(new cNormalShip(Scene, CoordChanges, 1, Vec3(22, 22)));

	return true;
}

bool cGame::Loop(float dt) {
	bool res = Process(dt);
	if(res) Render();

	return res;
}

void cGame::Finalize() {
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y) {
}

//Process
bool cGame::Process(float dt) {
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;
	
	if(keys[GLUT_KEY_UP])			Player.Jump();
	if(keys[GLUT_KEY_LEFT])			Player.MoveLeft();
	else if(keys[GLUT_KEY_RIGHT])	Player.MoveRight();
	else Player.Stop();	
	//Game Logic
	Player.Logic();
	//for (int i = 0; i < mEnemies.size(); ++i) mEnemies[i].doLogic(dt);

	return res;
}

//Output
void cGame::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();

	glPushMatrix();
	Scene.Draw();
	Player.Draw();

	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	
	//glRotatef(45.0f, 0.0f, 0.0f, 1.0f);	
	for (size_t i = 0; i < mEnemies.size(); ++i) {
		//Vec3 screen = CoordChanges.WorldToScreen(mEnemies[i]->mInitialWPosition);
		Vec3 screen(0, 0);
		glPushMatrix();
		//glTranslatef(-screen.x, -screen.y, 0);
		//glRotatef(45, 0, 0, 1);
		//glTranslatef(screen.x, screen.y, 0);
		mEnemies[i]->draw();
		glPopMatrix();

	}
	glutSwapBuffers();
}
