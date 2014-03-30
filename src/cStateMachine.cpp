#pragma once
#include "cStateMachine.hpp"
#include "cState.hpp"

cState* cStateMachine::GetState() const { return mActualState;}
void cStateMachine::SetState(cState* s) {
  mActualState = s;
  mActualState->reset(Timer::getTNow());}

