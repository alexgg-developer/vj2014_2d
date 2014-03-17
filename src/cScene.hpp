#pragma once
#include <vector>
#include "cTexture.hpp"

#define TILE_SIZE		16
#define BLOCK_SIZE		24

#define SCENE_Xo		(2*TILE_SIZE)
#define SCENE_Yo		TILE_SIZE

struct cScene {
  cScene();
  virtual ~cScene();

  bool Init();
  bool LoadLevel(int level);
  void Draw();

  int operator()(unsigned int x, unsigned int y) const {
	  return map[x][y]; }
private:
  std::vector<std::vector<int>> map;
  int id_DL;				//actual level display list
  cTexture mText;
};
