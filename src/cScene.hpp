#pragma once
#include <vector>
#include "cTexture.hpp"
#include "cObstacle.hpp"
#include "cCoordChanges.hpp"
#undef max
#include <algorithm>

struct cScene {
  cScene(cCoordChanges const& cc);
  virtual ~cScene();

  bool Init();
  bool LoadLevel(int level);
  void Draw() const;
  bool CollisionInClosedArea(int const x0, int const x1, int const y0, int const y1) const;

  int operator()(int const x, int const y) const {
	  return map[std::max<int>(0,x)][std::max<int>(0,y)]; }
private:
  cCoordChanges const& mCoordChanges;
  std::vector<std::vector<int>> map;
  std::vector<cObstacle> mObstacles;
  int id_DL;				//actual level display list
  cTexture mText;
};
