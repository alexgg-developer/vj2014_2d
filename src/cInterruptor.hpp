#pragma once
#include "cBicho.hpp"
struct cPuerta;
struct cPlayer;

/// When awake and collides with player passes to the next level
struct cInterruptor: public cBicho {
  cInterruptor(cScene const& map, cCoordChanges const& ch, cPlayer& pl, cPuerta & pu);
  ~cInterruptor();

  bool Init();
  virtual void doLogic(float const t, float const dt) override;
  virtual void Draw(float const t, float const dt) const override;
  virtual void setActive(bool const b) { mActive = b; }
  virtual void reset() override {
    setActive(true);
    cBicho::reset();
  }
protected:
  bool mActive;
  cPuerta& mPuerta;
  cPlayer& mPlayer;
};
