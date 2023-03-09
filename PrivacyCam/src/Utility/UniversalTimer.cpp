#include "UniversalTimer.h"

#include <iostream>

using namespace pricam;

UniversalTimer::UniversalTimer() :
	m_timingFinished(false)
{
}

UniversalTimer::~UniversalTimer()
{
	for (const auto& [fst, snd] : m_timePoints)
	{
		std::cout << fst << " " << snd.DurationSum / snd.DurationCount << std::endl;
	}
}

TimerHandle UniversalTimer::StartTimer(std::string& _sectionName)
{
	m_timePoints.try_emplace(_sectionName, TimeSlices());
	return &_sectionName;
}

void UniversalTimer::EndTimer(TimerHandle _handle)
{
	const auto& nowTimePoint = std::chrono::steady_clock::now();
	const std::string key = *static_cast<std::string*>(_handle);
	auto& timeSlice = m_timePoints[key];
	timeSlice.DurationCount++;
	timeSlice.DurationSum += 
		static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(nowTimePoint - timeSlice.StartTimePoint).count()) / 1000000;
	timeSlice.StartTimePoint = nowTimePoint;
}

