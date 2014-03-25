#pragma once
#include "cBicho.hpp"

/// State for a bicho
struct cState {
  cState(cBicho& csm) : mStateMachine(csm), mNextOnStop(nullptr) {}
  void setNextOnStop(cState* cs) { mNextOnStop=cs; }
  virtual void Stop() {
    if(mNextOnStop!=nullptr)
      mStateMachine.SetState(mNextOnStop);
  }
  virtual void reset() { mAnimation.reset(); }
  cFrame getFrame() { return mAnimation.Generate(); }
  cAni& getAni() { return mAnimation; }

protected:
  cBicho& mStateMachine;
  cState* mNextOnStop; //!< Non-ownership semantics not enforced through weak_ptr for locking
  cAni mAnimation;
};
