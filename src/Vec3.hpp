#pragma once
#include "Globals.hpp"

struct Vec3 {	
  float x, y, z;

  Vec3() {};
  Vec3(Vec3 const & v) : x(v.x), y(v.y), z(v.z) {}
  Vec3 (float const xPos, float const  yPos, float const  zPos = 0) : x(xPos), y(yPos), z(zPos) {};
  Vec3 operator+(Vec3 const& ot) const {
    return Vec3(x+ot.x, y+ot.y, z+ot.z); }
  Vec3 operator*(float const f) const {
    return Vec3(x*f, y*f, z*f); }
  Vec3 & Vec3::operator+=(const Vec3 &v) {
	  x += v.x;
	  y += v.y;
	  z += v.z;
	  return *this;
  }
  Vec3 operator-() const {
    return Vec3(-x,-y,-z); }
  bool operator==(const Vec3 &v) const
  {
	  return (x == v.x && y == v.y && z == v.z);
  }
};
