#ifndef PRICAM_UNIVERSAL_TIMER_H
#define PRICAM_UNIVERSAL_TIMER_H

#include <chrono>
#include <PreProcessors.h>
#include <unordered_map>

namespace pricam
{
	using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
	using TimerHandle = void*;

	struct TimeSlices
	{
		TimePoint StartTimePoint;
		double DurationSum;
		unsigned int DurationCount;

		TimeSlices() :
			StartTimePoint(std::chrono::steady_clock::now()),
			DurationSum(0),
			DurationCount(0)
		{
		}
	};

	class UniversalTimer
	{
		bool m_timingFinished;
		TimePoint m_startTime;
		std::unordered_map<std::string, TimeSlices> m_timePoints;

	public:
		UniversalTimer(const UniversalTimer& _other) = delete;
		UniversalTimer(UniversalTimer&& _other) noexcept = delete;
		UniversalTimer& operator=(const UniversalTimer& _other) = delete;
		UniversalTimer& operator=(UniversalTimer&& _other) noexcept = delete;

		DllExport UniversalTimer();
		DllExport ~UniversalTimer();

		DllExport TimerHandle StartTimer(std::string& _sectionName);
		DllExport void EndTimer(TimerHandle _handle);
	};
}

#endif // PRICAM_UNIVERSAL_TIMER_H