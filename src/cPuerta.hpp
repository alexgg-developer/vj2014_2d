#pragma once
#include "cBicho.hpp"
struct cPlayer;
struct cGame;

/// When awake and collides with player passes to the next level
/// TODO: cPuerta no puede controlar el cambio de nivel. No hay tiempo para hacerlo mejor. Mierda.
struct cPuerta: public cBicho {
  cPuerta(cScene const& map, cCoordChanges const& ch, cPlayer& player, cGame* const aGame, int const nextLev);
  ~cPuerta();

  bool Init();
  virtual void doLogic(float const t, float const dt) override;
  virtual void Draw(float const t, float const dt) const override;
  void activate() { mActive=true; }
  void setActive(bool const b) { mActive = b; }
  virtual void reset() override { 
    setActive(false);
    cBicho::reset();
    mNextLevTime=-1;
  }
protected:
  bool mActive;
  cPlayer& mPlayer;
  cGame* mGame;
  int const mNextLev;
  float mNextLevTime=-1;
  cTexture mWin, mWin2;
};
