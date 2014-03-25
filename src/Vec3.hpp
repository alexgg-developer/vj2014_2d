#pragma once
#include "Globals.hpp"

struct Vec3 {	
  float x, y, z;

  Vec3() {};
  Vec3 (float const xPos, float const  yPos, float const  zPos = 0) : x(xPos), y(yPos), z(zPos) {};
  Vec3 operator+(Vec3 const& ot) const {
    return Vec3(x+ot.x, y+ot.y, z+ot.z); }
  Vec3 operator*(float const f) const {
    return Vec3(x*f, y*f, z*f); }
};
