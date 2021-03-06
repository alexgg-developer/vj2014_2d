#pragma once
#include "cAni.hpp"
#include "cBicho.hpp"
struct cGame;
struct cScene;

struct cExplosion : public cBicho {
  cExplosion(cScene const& map, cCoordChanges const& ch);
  void start(float const t);
  bool hasFinished(float const t) const;
	virtual void Draw(float const t, float const dt) const override;
	virtual void doLogic(float const t, float const dt) override {}//TODO: Auto-destroy here?

  static void initialize(cScene* aGame) {
    mScene=aGame; }
  static void addExplosion(cScene const& map, cCoordChanges const& ch, Vec3 const& posW);
  static cScene* mScene;
  
protected:
  cAni mAnimation;
};
