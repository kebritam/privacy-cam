#ifndef PRICAM_TIMER_H
#define PRICAM_TIMER_H

#include <chrono>
#include <PreProcessors.h>

namespace pricam
{
	class Timer
	{
		std::chrono::time_point<std::chrono::steady_clock> m_startTime;
		double* m_duration;

	public:
		Timer(const Timer& _other) = delete;
		Timer(Timer&& _other) noexcept = delete;
		Timer& operator=(const Timer& _other) = delete;
		Timer& operator=(Timer&& _other) noexcept = delete;

		explicit DllExport Timer(double* _duration);
		DllExport ~Timer();

		DllExport void EndTimer() const;
	};
}

#endif // PRICAM_TIMER_H
