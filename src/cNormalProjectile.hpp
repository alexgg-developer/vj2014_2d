#pragma once
#include "cProjectile.hpp"

struct cNormalProjectile: public cProjectile {
	cNormalProjectile(cScene const& map, cCoordChanges const& ch);
};