#include "StopWatch.h"

using namespace ve;

StopWatch::StopWatch()
{
	start = std::chrono::high_resolution_clock::now();
}

long long StopWatch::Delta()
{
	//set previous time
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	start = stop;
	return duration.count();
}

long long StopWatch::Split() const
{
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
	return duration.count();
}