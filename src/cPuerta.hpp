#pragma once
#include "cBicho.hpp"
struct cPlayer;

/// When awake and collides with player passes to the next level
struct cPuerta: public cBicho {
  cPuerta(cScene const& map, cCoordChanges const& ch, cPlayer& player);
  ~cPuerta();

  bool Init();
  virtual void doLogic(float dt) override;
  void Draw() const;
  void activate() { mActive=true; }
protected:
  bool mActive;
  cPlayer& mPlayer;
};
