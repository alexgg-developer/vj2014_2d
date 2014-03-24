#include "Timer.hpp"
#include <omp.h>

void Timer::startTime()
{
	mStartTime = steady_clock::now();
}


float Timer::getDeltaTime()
{
	duration<float> elapsed_seconds = steady_clock::now() - mStartTime;
	mStartTime = steady_clock::now();

	
	return elapsed_seconds.count();
}

void Timer::reset()
{
	//duration<float> t = steady_clock::duration::zero();
	//time_point<steady_clock> tt(t.);
	//mStartTime = tt;
	//steady_clock::time_point<steady_clock, duration<float>> t(steady_clock::duration::zero);
}
