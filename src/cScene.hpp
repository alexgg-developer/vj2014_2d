#pragma once
#include <vector>
#include "cTexture.hpp"
#include "cObstacle.hpp"
#include "cCoordChanges.hpp"
#undef max
#undef min
#include <algorithm>

struct cScene {
  cScene(cCoordChanges const& cc);
  virtual ~cScene();

  bool Init();
  bool LoadLevel(int level);
  void Draw() const;
  bool CollisionInClosedArea(Vec3 const& world0, Vec3 const& world1) const;

  int operator()(int const x, int const y) const {
	  return map[std::min<int>(std::max<int>(0,x),map.size()-1)][std::min<int>(std::max<int>(0,y),map[0].size()-1)]; }
private:
  cCoordChanges const& mCoordChanges;
  std::vector<std::vector<int>> map;
  std::vector<cObstacle> mObstacles;
  int id_DL;				//actual level display list
  cTexture mText;
};
