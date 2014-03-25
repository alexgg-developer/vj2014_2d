#pragma once
#include <chrono>

using namespace std::chrono;

struct Timer
{
	steady_clock::time_point mStartTime;

	Timer() : mStartTime(steady_clock::duration::zero()) {};
	void startTime();
	float getDeltaTime();
	void reset();

};

