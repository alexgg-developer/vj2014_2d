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
  //TODO Draw modifies the object. Oh shit. kill kill kill kill kill kill kill kill kill kill ikill oh, that may be a new apple product kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
  virtual void doLogic(float dt) override;
  void Draw();
  void Attack();
  void Attack(Vec3 const & direction, cElementalProjectile::KindOfElement element);
};
