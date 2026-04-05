#include "LifetimeTimer.h"
#include "../logging/LogManager.h"

namespace ve
{

	LifetimeTimer::LifetimeTimer(const std::string& name)
		: timerName{ name }
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	LifetimeTimer::~LifetimeTimer()
	{
		auto endTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
		VE_LOG(std::format("LifetimeTimer [{}] duration: {} ms", timerName, duration));
	}

}