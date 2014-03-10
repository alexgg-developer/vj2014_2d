#pragma once

#include "cTexture.hpp"
#include "Globals.hpp"

//Image array size
#define NUM_IMG		2

//Image identifiers
#define IMG_BLOCKS	0
#define IMG_PLAYER	1
/*
#define IMG_ENEMY1	2
#define IMG_ENEMY2	3
#define IMG_SHOOT	4
...
*/

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	std::tuple<int,int> GetSize(int img);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

private:
	cTexture texture[NUM_IMG];
};
