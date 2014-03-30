#pragma once
#include "cBicho.hpp"
#include "Timer.hpp"
#include "cAni.hpp"
#include "cStateMachine.hpp"

/// State for a bicho
struct cState {
  cState(cStateMachine* csm) : mStateMachine(csm), mNextOnUnJump(nullptr), mNextOnStop(nullptr), mNextOnLeft(nullptr),
   mNextOnRight(nullptr), mNextOnJump(nullptr), mNextOnAnimationFinished(nullptr), mNextOnActivate(nullptr) {}
  void setNextOnStop(cState* cs) { mNextOnStop = cs; }
  void setNextOnRight(cState* cs) { mNextOnRight = cs; }
  void setNextOnLeft(cState* cs) { mNextOnLeft = cs; }
  void setNextOnJump(cState* cs) { mNextOnJump = cs; }
  void setNextOnUnJump(cState* cs) { mNextOnUnJump = cs; }
  void setNextOnActivate(cState* cs) { mNextOnActivate = cs; }
  void setNextOnAnimationFinished(cState* cs) { mNextOnAnimationFinished = cs; }

  virtual void Stop() {
    if(mNextOnStop!=nullptr)
      mStateMachine->SetState(mNextOnStop); }
  virtual void Left() {
    if(mNextOnLeft!=nullptr)
      mStateMachine->SetState(mNextOnLeft); }
  virtual void Right() {
    if(mNextOnRight!=nullptr)
      mStateMachine->SetState(mNextOnRight); }
  virtual void Jump() {
    if(mNextOnJump!=nullptr)
      mStateMachine->SetState(mNextOnJump); }
  virtual void UnJump() {
    if(mNextOnUnJump!=nullptr)
      mStateMachine->SetState(mNextOnUnJump); }
  virtual void Activate() {
    if(mNextOnActivate!=nullptr)
      mStateMachine->SetState(mNextOnActivate); }
  virtual void reset(float const t) { mAnimation.reset(t); }
  cFrame getFrame(float const t) { 
    if(mNextOnAnimationFinished && mAnimation.isInLastFrame(t)) {
      mStateMachine->SetState(mNextOnAnimationFinished);
    }
    return mAnimation.Generate(t); }
  cAni& getAni() {
    return mAnimation; }

protected:
  cStateMachine* mStateMachine;
  cState* mNextOnStop, *mNextOnRight, *mNextOnLeft, *mNextOnJump, *mNextOnUnJump, *mNextOnAnimationFinished, *mNextOnActivate; //!< Non-ownership semantics not enforced through weak_ptr for locking
  cAni mAnimation;
};
