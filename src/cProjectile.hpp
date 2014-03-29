#pragma once
#include <memory>
#include "cPhysics.hpp"
#include "cTexture.hpp"
#include "Vec3.hpp"
#include "cCoordChanges.hpp"
#include "cBicho.hpp"

struct cProjectile : public cBicho {
	void changePhysics(Vec3 const& force, Vec3 const& maxSpeed, Vec3 const& speed);
	bool mAwake;
	int mDamage;

	cProjectile(cScene const& map, cCoordChanges const& ch) : cBicho(map, ch) {}
  virtual void Draw(float const t, float const dt) const override;
  void changeDirection(Vec3 const & direction) { mPhysics->changeDirection(direction);}
	virtual void doLogic(float const t, float const dt) override;
protected:
	std::shared_ptr<cPhysics> mPhysics;
	void move(Vec3 const& speed, float const dt);
};