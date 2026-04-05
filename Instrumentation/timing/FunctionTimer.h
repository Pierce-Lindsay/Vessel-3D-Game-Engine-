#pragma once
#include <format>
#include <chrono>
#include "TimeLog.h"

/// <summary>
/// Measures the time taken by a function to execute with the given number of iterations. Returns a TimeLog containing 
/// the duration of each iteration and the average duration of the function execution. Also logs the results to the log file.
/// Parameters for the the function can be passed as variadic arguments.
/// </summary>
#define VE_TIME_MEASURE(iterations, func, ...) measureFunctionTimeRigorous(iterations, #func,  func, __VA_ARGS__)

namespace ve
{ 
	/// <summary>
	/// Measures the time taken by a function to execute. Returns the duration 
	/// of the function execution as a std::chrono::high_resolution_clock::duration.
	/// Parameters for the the function can be passed as variadic arguments.
	/// </summary>
	template<typename Func, typename... Args>
	std::chrono::high_resolution_clock::duration measureFunctionTime(Func f, Args... args) 
	{
		auto startTime = std::chrono::high_resolution_clock::now();
		f(args...);
		auto endTime = std::chrono::high_resolution_clock::now();
		return endTime - startTime;
	}

	/// <summary>
	/// Measures the time taken by a function to execute with the given number of iterations. Returns a TimeLog containing 
	/// the duration of each iteration and the average duration of the function execution. Also logs the results to the log file.
	/// Parameters for the the function can be passed as variadic arguments.
	/// </summary>
	template<typename Func, typename... Args>
	TimeLog measureFunctionTimeRigorous(int iterations, const std::string& name, Func f, Args... args)
	{
		TimeLog log(name);
		for (int i = 0; i < iterations; ++i) {
			log.AddLap(measureFunctionTime(f, args...));
		}
		log.LogInfo();
		return log;
	}
}