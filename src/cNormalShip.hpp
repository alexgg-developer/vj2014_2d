#pragma once

#include "cEnemy.hpp"
#include "cNormalProjectile.hpp"
#include <vector>
#include <memory>

struct cNormalShip: public cEnemy {
	cNormalShip(cPlayer& pl, cScene const& map, cCoordChanges const& ch, bool awake);
	cNormalShip(cPlayer& pl, cScene const& map, cCoordChanges const& ch, int life, bool awake);
	cNormalShip(cPlayer& pl, cScene const& map, cCoordChanges const& ch, int life, Vec3 const& tilePosition, bool awake);
	virtual void doLogic(float const t, float const dt) override;
	virtual void Draw(float const t, float const dt) const override;

protected:
	std::vector<std::shared_ptr<cNormalProjectile>> mProjectiles;
};
