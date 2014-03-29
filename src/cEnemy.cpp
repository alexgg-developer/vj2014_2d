#include "cEnemy.hpp"

cEnemy::cEnemy(cScene const& map, cCoordChanges const& ch, int life, std::shared_ptr<cPhysics>& physics)
 : mLife(life), mPhysics(physics), cBicho(map, ch) 
{
	//mInitialWPosition = mCoordChanges.TileToWorld(Vec3(10, 10));
}

void cEnemy::setInitialTilePosition(Vec3 const& tilePosition)
{
	posW = mCoordChange.TileToWorld(tilePosition);
}
void cEnemy::Draw(float const t, float const dt) const
{
	if (mAwake) {
		Vec3 const screen = mCoordChange.WorldToScreen(posW);
		glPushMatrix();
		glTranslatef(screen.x, screen.y, 0);
		mText.drawAlternative(Vec3(0, 0), Vec3(1, 1), Vec3(0, 0), Vec3(w, h));
		glPopMatrix();
	}
}
void cEnemy::move(Vec3 const& speed, float dt) {
  Vec3 const deltaWPos = (speed * dt);
  Vec3 const backup = posW;
  cRect const bbox0 = this->GetBBox();
	posW += deltaWPos;
  cRect const bbox1 = this->GetBBox();
  cRect const augmentedBbox = bbox0.unite(bbox1);
  if(mMap.CollisionInClosedArea(augmentedBbox)) {
    posW = backup; }
}
