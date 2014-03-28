#pragma once
#include "cProjectile.hpp"

struct cElementalProjectile: public cProjectile
{
	enum KindOfElement{ FIRE, ICE, ELECTRIC };
	cElementalProjectile(cScene const& map, cCoordChanges const& ch, KindOfElement element);
protected:
	KindOfElement mElement;

};