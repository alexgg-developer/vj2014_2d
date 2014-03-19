#pragma once
#include "Globals.hpp"

struct Position {	
	int x, y, z;

	Position() {};
	Position(int xPos, int yPos, int zPos = 0) : x(xPos), y(yPos), z(zPos) {};
};