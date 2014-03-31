#include "cEnemy.hpp"
#include "cPlayer.hpp"
#include "cCoordChanges.hpp"
#include "cScene.hpp"

cEnemy::cEnemy(cPlayer& pl, cScene const& map, cCoordChanges const& ch, int life, std::shared_ptr<cPhysics>& physics)
 : mPhysics(physics), cBicho(map, ch), mPlayer(pl)
{
  mLife = life;
	//mInitialWPosition = mCoordChanges.TileToWorld(Vec3(10, 10));
}
cEnemy::cEnemy(cPlayer& pl, cScene const& map, cCoordChanges const& ch) :  cBicho(map, ch), mPlayer(pl) { mLife=1;};
cEnemy::cEnemy(cPlayer& pl, cScene const& map, cCoordChanges const& ch, int life) : cBicho(map, ch), mPlayer(pl) {
  mLife = life;};

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
bool cEnemy::CollidesWithPlayer() const {
  return mPlayer.GetBBox().collides(GetBBox());
}
cEnemy* cEnemy::CollidesWithEnemies() {
  auto& enL = mMap.EnemiesList();
  for(auto& en : enL) {
    if(en->GetBBox().collides(GetBBox())) {
      return en;
    }
  }
  return nullptr;
}
