#pragma once
#include <vector>
#include "cTexture.hpp"

struct cScene {
  cScene();
  virtual ~cScene();

  bool Init();
  bool LoadLevel(int level);
  void Draw();

  int operator()(unsigned int x, unsigned int y) const {
	  return map[x][y]; }
  
  unsigned int const getTileSize() const { return mTileSize;}
  unsigned int const getBlockSize() const { return mBlockSize;}
  unsigned int const getOriginX() const { return mOriginX;}
  unsigned int const getOriginY() const { return mOriginY;}
private:
  std::vector<std::vector<int>> map;
  int id_DL;				//actual level display list
  cTexture mText;
  unsigned int const mTileSize;
  unsigned int const mBlockSize;
  unsigned int const mOriginX;
  unsigned int const mOriginY;
};
