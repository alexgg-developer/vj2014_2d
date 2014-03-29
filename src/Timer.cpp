#include "Timer.hpp"

float Timer::getActualTime() const {
  return mStartTime.time_since_epoch().count() - sBeginTime.time_since_epoch().count();
}
float Timer::getDeltaTime() const {
	duration<float> elapsed_seconds = steady_clock::now() - mStartTime;
	
	return (elapsed_seconds.count());
}

void Timer::reset() {
	mStartTime = steady_clock::now(); }

float Timer::getTNow() {
  static bool init=false;
  if(!init) {
    sBeginTime = steady_clock::now();
    init=true;
  }
  return steady_clock::now().time_since_epoch().count() - sBeginTime.time_since_epoch().count();
}
steady_clock::time_point Timer::sBeginTime = steady_clock::now();