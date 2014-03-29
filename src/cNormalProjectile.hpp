#pragma once
#include "cProjectile.hpp"

struct cNormalProjectile: public cProjectile {
	cNormalProjectile(cPlayer& pl, cScene const& map, cCoordChanges const& ch);
};