#pragma once
#include "cBicho.hpp"
struct cPlayer;

/// When awake and collides with player passes to the next level
struct cPuerta: public cBicho {
  cPuerta(cScene const& map, cCoordChanges const& ch, cPlayer& player);
  ~cPuerta();

  bool Init();
  virtual void doLogic(float const t, float const dt) override;
  virtual void Draw(float const t, float const dt) const override;
  void activate() { mActive=true; }
protected:
  bool mActive;
  cPlayer& mPlayer;
};
