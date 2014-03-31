#pragma once
#include <string>
#include "cBicho.hpp"
#include "cTexture.hpp"

struct cHud : public cBicho {
  cHud(cScene const& map, cCoordChanges const& ch);
	bool Init();
	virtual void update(int life);
	virtual void Draw(float const t, float const dt) const override;
	virtual void doLogic(float const t, float const dt) override {} //TODO Make it destructable
  protected:
	  cTexture mHeartFull, mHeartEmpty;
	  const int mHeartWidth  = 32;
	  const int mHeartHeight = 32;
	  int mLife;
};
