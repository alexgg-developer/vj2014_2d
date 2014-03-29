#pragma once
#include <vector>
#include "cTexture.hpp"
#include "cObstacle.hpp"
#include "cCoordChanges.hpp"
#include "cPuerta.hpp"
#include "cInterruptor.hpp"
#undef max
#undef min
#include <algorithm>
struct cPlayer;

struct cScene {
  cScene(cCoordChanges const& cc, cPlayer& pl);
  virtual ~cScene();

  bool Init();
  bool LoadLevel(int level);
  void Draw(float const t, float const dt) const;
  bool CollisionInClosedArea(cRect const& world) const;
  void doLogic(float const t, float const dt);

  int operator()(int const x, int const y) const {
	  return map[std::min<int>(std::max<int>(0,x),map.size()-1)][std::min<int>(std::max<int>(0,y),map[0].size()-1)]; }
private:
  cCoordChanges const& mCoordChanges;
  std::vector<std::vector<int>> map;
  std::vector<cObstacle> mObstacles;
  int id_DL;				//actual level display list
  cTexture mText;
  cPuerta mExitDoor;
  cInterruptor mInterruptor;
};
