#include "cGame.hpp"
#include "Globals.hpp"


cGame::cGame(void) : CoordChanges(), Scene(CoordChanges), Player(Scene, CoordChanges) { }

cGame::~cGame(void) { }

bool cGame::Init() {
	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
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
	Player.SetTile(Vec3(2,1)); //Initial tile
	Player.SetState(STATE_LOOKRIGHT);

	//Enemy initialization
	mEnemies.push_back(cEnemy(Scene, CoordChanges, 3));

	return true;
}

bool cGame::Loop() {
	bool res = Process();
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
bool cGame::Process() {
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;
	
	if(keys[GLUT_KEY_UP])			Player.Jump();
	if(keys[GLUT_KEY_LEFT])			Player.MoveLeft();
	else if(keys[GLUT_KEY_RIGHT])	Player.MoveRight();
	else Player.Stop();	
	//Game Logic
	Player.Logic();
	//for (int i = 0; i < mEnemies.size(); ++i) mEnemies[i].doLogic();

	return res;
}

//Output
void cGame::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();

	Scene.Draw();
	Player.Draw();
	for (size_t i = 0; i < mEnemies.size(); ++i) mEnemies[i].draw();

	glutSwapBuffers();
}
