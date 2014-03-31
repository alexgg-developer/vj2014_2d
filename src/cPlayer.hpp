#pragma once
#include "cBicho.hpp"
#include "cElementalProjectile.hpp"
#include <vector>

struct cPlayer: public cBicho {
  cPlayer(cScene const& map, cCoordChanges const& ch);
  ~cPlayer();

  bool Init();
  virtual void doLogic(float const t, float const dt) override;
  virtual void Draw(float const t, float const dt) const override;
  void Attack();
  void Attack(Vec3& direction, cElementalProjectile::KindOfElement element);
  virtual void reset() override {
    mAttacks.clear();
    cBicho::reset();
  }

	std::vector<cElementalProjectile> mAttacks;
};
