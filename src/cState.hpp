#pragma once
#include "cBicho.hpp"

/// State for a bicho
struct cState {
  cState(cBicho& csm) : mStateMachine(csm), mNextOnUnJump(nullptr), mNextOnStop(nullptr), mNextOnLeft(nullptr), mNextOnRight(nullptr), mNextOnJump(nullptr) {}
  void setNextOnStop(cState* cs) { mNextOnStop = cs; }
  void setNextOnRight(cState* cs) { mNextOnRight = cs; }
  void setNextOnLeft(cState* cs) { mNextOnLeft = cs; }
  void setNextOnJump(cState* cs) { mNextOnJump = cs; }
  void setNextOnUnJump(cState* cs) { mNextOnUnJump = cs; }

  virtual void Stop() {
    if(mNextOnStop!=nullptr)
      mStateMachine.SetState(mNextOnStop); }
  virtual void Left() {
    if(mNextOnLeft!=nullptr)
      mStateMachine.SetState(mNextOnLeft); }
  virtual void Right() {
    if(mNextOnRight!=nullptr)
      mStateMachine.SetState(mNextOnRight); }
  virtual void Jump() {
    if(mNextOnJump!=nullptr)
      mStateMachine.SetState(mNextOnJump); }
  virtual void UnJump() {
    if(mNextOnUnJump!=nullptr)
      mStateMachine.SetState(mNextOnUnJump); }
  virtual void reset() { mAnimation.reset(); }
  cFrame getFrame() { return mAnimation.Generate(); }
  cAni& getAni() { return mAnimation; }

protected:
  cBicho& mStateMachine;
  cState* mNextOnStop, *mNextOnRight, *mNextOnLeft, *mNextOnJump, *mNextOnUnJump; //!< Non-ownership semantics not enforced through weak_ptr for locking
  cAni mAnimation;
};
