#pragma once
struct cState;

struct cStateMachine {
  virtual cState* GetState() const;
  virtual void SetState(cState* s);
protected:
  cState* mActualState;
};
