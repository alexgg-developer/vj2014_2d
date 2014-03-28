#pragma once
#include "cBicho.hpp"
#include "cPuerta.hpp"

struct cPlayer;
/// When awake and collides with player passes to the next level
struct cInterruptor: public cBicho {
  cInterruptor(cScene const& map, cCoordChanges const& ch, cPlayer& pl, cPuerta & pu);
  ~cInterruptor();

  bool Init();
  virtual void doLogic(float dt) override;
  void Draw() const;
protected:
  bool mActive;
  cPuerta& mPuerta;
  cPlayer& mPlayer;
};
