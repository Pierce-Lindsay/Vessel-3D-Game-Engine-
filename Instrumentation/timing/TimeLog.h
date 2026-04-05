#pragma once
#include <chrono>
#include <vector>
#include <string>

namespace ve
{
	class TimeLog
	{
	private:
		std::string name = "undefined";
		size_t count = 0;
		std::vector<std::chrono::high_resolution_clock::duration> laps;

	public:
		TimeLog(const std::string& name)
			: name(name)
		{}

		/// <summary>
		/// Add a lap to the log. A lap is a duration of time that is added to the log.
		/// </summary>
		void AddLap(std::chrono::high_resolution_clock::duration duration);

		/// <summary>
		/// Calculate the average duration of the laps in the log. 
		/// Returns the average duration of the laps in the log.
		/// </summary>
		std::chrono::high_resolution_clock::duration GetAverage() const;

		/// <summary>
		/// Get the number of laps in the log.
		/// </summary>
		size_t GetCount() const;

		/// <summary>
		/// Get the laps in the log. A lap is a duration of time.
		/// </summary>
		const std::vector<std::chrono::high_resolution_clock::duration>& GetLaps() const;

		/// <summary>
		/// Calculate the standard deviation of the laps in the log.
		/// </summary>
		/// <returns></returns>
		double GetStandardDeviationMs() const;

		/// <summary>
		/// Finds and returns the min lap duration.
		/// </summary>
		std::chrono::high_resolution_clock::duration GetMin() const;

		/// <summary>
		/// Finds and returns the max lap duration.
		/// </summary>
		std::chrono::high_resolution_clock::duration GetMax() const;

		/// <summary>
		/// Gets the average lap duration in milliseconds.
		/// </summary>
		double GetAverageMs() const;
		
		/// <summary>
		/// Gets the average lap duration in nanoseconds.
		/// </summary>
		double GetAverageNs() const;

		/// <summary>
		/// Log the average, standard deviation, min, and max lap durations to the Log.
		/// </summary>
		void LogInfo() const;
	};
}