#pragma once
#include "Globals.hpp"

struct Vec3 {	
  float x, y, z;

  Vec3() {};
  Vec3 (int xPos, int yPos, int zPos = 0) : x(xPos), y(yPos), z(zPos) {};
};
