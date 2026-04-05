#include "TimeLog.h"
#include "../logging/logManager.h"
#include <cmath>

namespace ve
{

	void TimeLog::AddLap(std::chrono::high_resolution_clock::duration duration)
	{
		laps.push_back(duration);
		count++;
	}

	std::chrono::high_resolution_clock::duration TimeLog::GetAverage() const
	{
		if (laps.empty())
			return std::chrono::high_resolution_clock::duration(0);
		std::chrono::high_resolution_clock::duration totalDuration(0);
		for (const auto& lap : laps)
			totalDuration += lap;
		return totalDuration / count;
	}

	size_t TimeLog::GetCount() const
	{
		return count;
	}

	const std::vector<std::chrono::high_resolution_clock::duration>& TimeLog::GetLaps() const
	{
		return laps;
	}

	double TimeLog::GetStandardDeviationMs() const
	{
		if (count < 2)
			return 0.0;
		double average = GetAverageMs();

		double variance = 0.0;
		for (const auto& lap : laps)
		{
			double lapMs = std::chrono::duration_cast<std::chrono::milliseconds>(lap).count();
			auto diff = lapMs - average;
			variance += (diff * diff);
		}
		variance /= (count - 1);
		return sqrt(variance);
	}

	std::chrono::high_resolution_clock::duration TimeLog::GetMin() const
	{
		if (laps.empty())
			return std::chrono::high_resolution_clock::duration(0);
		auto minLap = laps[0];
		for (const auto& lap : laps)
			if (lap < minLap)
				minLap = lap;
		return minLap;
	}

	std::chrono::high_resolution_clock::duration TimeLog::GetMax() const
	{
		if (laps.empty())
			return std::chrono::high_resolution_clock::duration(0);
		auto maxLap = laps[0];
		for (const auto& lap : laps)
			if (lap > maxLap)
				maxLap = lap;
		return maxLap;
	}

	double TimeLog::GetAverageMs() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(GetAverage()).count();
	}

	double TimeLog::GetAverageNs() const
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(GetAverage()).count();
	}

	void TimeLog::LogInfo() const
	{
		VE_LOG(std::format("\n TimeLog Info [{}] \n Lap Count: {} \n Average: {} ms \n StdDev: {} ms \n Min: {} ms \n Max: {} ms \n",
			name,
			GetCount(),
			GetAverageMs(),
			GetStandardDeviationMs(),
			std::chrono::duration_cast<std::chrono::milliseconds>(GetMin()).count(),
			std::chrono::duration_cast<std::chrono::milliseconds>(GetMax()).count()));
	}

}