#pragma once
#include "cTexture.hpp"
#include "cObstacle.hpp"
#include "cCoordChanges.hpp"
#include "cPuerta.hpp"
#include "cInterruptor.hpp"
#include "cExplosion.hpp"
#include "cPlayer.hpp"
#undef max
#undef min
#include <algorithm>
#include <vector>
struct cEnemy;

/// TODO: Separate scene and map, it's getting bigger!
struct cScene {
  cScene();
  virtual ~cScene();

  bool Init();
  bool LoadLevel(int level);
  void Draw(float const t, float const dt) const;
  bool CollisionInClosedArea(cRect const& world) const;
  void doLogic(float const t, float const dt);

  int operator()(int const x, int const y) const {
	  return map[std::min<int>(std::max<int>(0,x),map.size()-1)][std::min<int>(std::max<int>(0,y),map[0].size()-1)]; }

  void addExplosion(cExplosion expl) { mExplosions.push_back(expl); }
  
	cPlayer Player;
  cCoordChanges CoordChanges;
private:
  std::vector<std::vector<int>> map;
  std::vector<cObstacle> mObstacles;
  int id_DL;				//actual level display list
  cTexture mText;
  cPuerta mExitDoor;
  cInterruptor mInterruptor;
	std::vector<cEnemy*> mEnemies;
  std::vector<cExplosion> mExplosions;
};
