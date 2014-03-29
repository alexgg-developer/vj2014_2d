#pragma once
#include <iostream>
#include <string>
#include <memory>

#include "Globals.hpp"
#include "cTexture.hpp"
#include "Vec3.hpp"
#include "cScene.hpp"
#include "cPhysics.hpp"
#include "cBicho.hpp"

struct cEnemy: public cBicho {
	cEnemy(cScene const& map, cCoordChanges const& ch) :  mLife(1), cBicho(map, ch) {};
	cEnemy(cScene const& map, cCoordChanges const& ch, int life) :  mLife(life), cBicho(map, ch) {};
	cEnemy(cScene const& map, cCoordChanges const& ch, int life, std::shared_ptr<cPhysics>& physics);
	void setInitialTilePosition(Vec3 const& tilePosition);
	virtual void Draw(float const t, float const dt) const override;

protected:
	void move(Vec3 const& speed, float dt);
	int mLife;
	float mOrientation;
	std::shared_ptr<cPhysics> mPhysics;
	bool mAwake;
};