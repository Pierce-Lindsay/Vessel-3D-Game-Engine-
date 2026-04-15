#pragma once
#include <chrono>
#include <string>

namespace ve
{
	class LifetimeTimer
	{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
		std::string timerName;
	public:
		/// <summary>
		/// Create a lifetime timer at start its lifetime.
		/// </summary>
		LifetimeTimer(const std::string& name);

		/// <summary>
		/// Destroy the lifetime timer. And return the total lifetime of the timer in microseconds.
		/// </summary>
		~LifetimeTimer();
	};
}