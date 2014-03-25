#pragma once
#include "cAni.hpp"
#include "cTexture.hpp"
#include "cBicho.hpp"
struct cGame;

struct cExplosion : public cBicho {
  cExplosion(cScene const& map, cCoordChanges const& ch);
  void start();
  bool hasFinished() const;
  void Draw();

  static void initialize(cGame* aGame) {
    mGame=aGame; }
  static void addExplosion(cScene const& map, cCoordChanges const& ch, Vec3 const& posW);
  static cGame* mGame;
  
protected:
  cAni mAnimation;
};
