#pragma once
#include "cTexture.hpp"
#include "cObstacle.hpp"
#include "cCoordChanges.hpp"
#include "cPuerta.hpp"
#include "cInterruptor.hpp"
#include "cExplosion.hpp"
#include "cPlayer.hpp"
#include "cStateMachine.hpp"
#undef max
#undef min
#include <algorithm>
#include <vector>
struct cEnemy;
struct cState;
struct cGame;

struct iScene {
  iScene(cGame* aGame) : mGame(aGame) {}
  virtual ~iScene(){}
  virtual void UpKey() {}
  virtual void DownKey() {}
  virtual void LeftKey() {}
  virtual void RightKey() {}
  virtual void Stop() {}
  virtual void Attack(Vec3& direction, cElementalProjectile::KindOfElement el) {}
  virtual void doLogic(float const t, float const dt) =0;
  virtual void Draw(float const t, float const dt) const =0;
  virtual bool Init() =0;
  virtual bool LoadLevel(int level)=0;
  virtual void PressedEnter() {}
  virtual bool AvoidRepetitionsS() { return false; }
protected:
  cGame* mGame;
};

struct cMenu : public iScene, public cStateMachine {
  cMenu(cGame* aG) : iScene(aG) {}
  virtual void UpKey() override;
  virtual void DownKey() override;
  virtual void LeftKey() override;
  virtual void RightKey() override;
  virtual void doLogic(float const t, float const dt) override;
  virtual void Draw(float const t, float const dt) const override;
  virtual bool Init() override;
  virtual bool LoadLevel(int level) override;
  virtual void PressedEnter() override;
  virtual bool AvoidRepetitionsS() override { return true; }
protected:
  enum MenuState {
    ENTER=0,
    LEVEL0=1,
    LEVEL1=2,
    EXIT=3,
    CREDITS=4};
  std::array<std::shared_ptr<cState>, 4> mStates;
  std::array<cTexture,9> mTextures;
};

/// TODO: Separate scene and map, it's getting bigger!
struct cScene : public iScene {
  cScene(cGame* aG, int const nextLev);
  virtual ~cScene();

  bool Init();
  bool LoadLevel(int level);
  virtual void Draw(float const t, float const dt) const override;
  bool CollisionInClosedArea(cRect const& world) const;
  void doLogic(float const t, float const dt) override;

  int operator()(int const x, int const y) const {
	  return map[std::min<int>(std::max<int>(0,x),map.size()-1)][std::min<int>(std::max<int>(0,y),map[0].size()-1)]; }

  void addExplosion(cExplosion expl) { mExplosions.push_back(expl); }
  virtual void UpKey() override {Player.Jump(); }
  virtual void LeftKey() override {Player.MoveLeft();}
  virtual void RightKey() override {Player.MoveRight();}
  virtual void Stop() override { Player.Stop(); }
  virtual void Attack(Vec3& direction, cElementalProjectile::KindOfElement el) override {Player.Attack(direction, el); }
  
  cPlayer Player;
  cCoordChanges CoordChanges;
private:
  std::vector<std::vector<int>> map;
  std::vector<cObstacle> mObstacles;
  int id_DL;				//actual level display list
  cTexture mText;
  cPuerta mExitDoor;
  cInterruptor mInterruptor;
  std::vector<cEnemy*> mEnemies;
  std::vector<cExplosion> mExplosions;
};
