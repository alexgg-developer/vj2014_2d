#pragma once
#include <memory>
#include "cEnemy.hpp"
struct cPhysics;
struct cCoordChanges;
struct cPlayer;

struct cProjectile : public cEnemy {
	cProjectile(cPlayer& pl, cScene const& map, cCoordChanges const& ch);
  virtual void Draw(float const t, float const dt) const override;
  void changeDirection(Vec3 const & direction);
	virtual void doLogic(float const t, float const dt) override;
	void changePhysics(Vec3 const& force, Vec3 const& maxSpeed, Vec3 const& speed);
  bool Awake() const { return mAwake; }
  void AffectEnemies(bool const b) { mAffectsEnemies = b; }
  void AffectsProta(bool const b) { mAffectsProta = b; }

	bool mAwake=true; //TODO: Protect it
protected:
	std::shared_ptr<cPhysics> mPhysics;
	void move(Vec3 const& speed, float const dt);
	int mDamage;
  bool mAffectsProta=false;
  bool mAffectsEnemies=false;
};