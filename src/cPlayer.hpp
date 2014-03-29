#pragma once
#include "cBicho.hpp"
#include "cScene.hpp"
#include "cElementalProjectile.hpp"

#include <vector>

struct cPlayer: public cBicho {

	std::vector<cElementalProjectile> mAttacks;
  cPlayer(cScene const& map, cCoordChanges const& ch);
  ~cPlayer();

  bool Init();
  virtual void doLogic(float const t, float const dt) override;
  virtual void Draw(float const t, float const dt) const override;
  void Attack();
  void Attack(Vec3 const & direction, cElementalProjectile::KindOfElement element);
};
