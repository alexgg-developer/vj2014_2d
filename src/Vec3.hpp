#pragma once
#include "Globals.hpp"

struct Vec3 {	
  float x, y, z;

  Vec3() {};
  Vec3 (float const xPos, float const  yPos, float const  zPos = 0) : x(xPos), y(yPos), z(zPos) {};
};
