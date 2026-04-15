#pragma once
#include <chrono>

namespace ve
{
	class StopWatch
	{
	private:
		//previous time the clock cares about
		std::chrono::steady_clock::time_point start;

	public:
		StopWatch();

		/// <summary>
		/// Gets the time between the last delta call.
		/// </summary>
		/// <returns>Time elapsed since last delta call.</returns>
		long long Delta();

		/// <summary>
		/// Gets the time between the last delta call.
		/// </summary>
		/// <returns>Time elapsed since last delta call.</returns>
		long long Split() const;
	};
}