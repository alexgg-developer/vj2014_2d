#pragma once
#include <memory>
#include "cBicho.hpp"
struct cScene;
struct cPhysics;
struct cPlayer;

struct cEnemy: public cBicho {
	cEnemy(cPlayer& pl, cScene const& map, cCoordChanges const& ch);
	cEnemy(cPlayer& pl, cScene const& map, cCoordChanges const& ch, int life);
	cEnemy(cPlayer& pl, cScene const& map, cCoordChanges const& ch, int life, std::shared_ptr<cPhysics>& physics);
	void setInitialTilePosition(Vec3 const& tilePosition);
	virtual void Draw(float const t, float const dt) const override;
  bool CollidesWithPlayer() const;
  virtual bool WantsToDestroyItself() const override { return mLife<=0; }

protected:
	void move(Vec3 const& speed, float dt);
	int mLife;
	float mOrientation;
	std::shared_ptr<cPhysics> mPhysics;
	bool mAwake;
  cPlayer& mPlayer;
};