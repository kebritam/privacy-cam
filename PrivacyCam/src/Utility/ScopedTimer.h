#ifndef PRICAM_SCOPED_TIMER_H
#define PRICAM_SCOPED_TIMER_H

#include <chrono>
#include <PreProcessors.h>

namespace pricam
{
	class ScopedTimer
	{
		std::chrono::time_point<std::chrono::steady_clock> m_startTime;
		double* m_duration;
		bool m_timingFinished;

	public:
		ScopedTimer(const ScopedTimer& _other) = delete;
		ScopedTimer(ScopedTimer&& _other) noexcept = delete;
		ScopedTimer& operator=(const ScopedTimer& _other) = delete;
		ScopedTimer& operator=(ScopedTimer&& _other) noexcept = delete;

		explicit DllExport ScopedTimer(double* _duration);
		DllExport ~ScopedTimer();

		DllExport void EndTimer();
	};
}

#endif // PRICAM_SCOPED_TIMER_H
