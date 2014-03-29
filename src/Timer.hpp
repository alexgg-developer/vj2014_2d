#pragma once
#include <chrono>

using namespace std::chrono;

struct Timer
{
	steady_clock::time_point mStartTime;

	Timer() : mStartTime(steady_clock::duration::zero()) {};
	float getDeltaTime() const;
	void reset();
  float getActualTime() const;

  static float getTNow();
  static steady_clock::time_point sBeginTime;
};

