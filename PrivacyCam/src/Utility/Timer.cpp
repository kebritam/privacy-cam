#include "Timer.h"

using namespace pricam;

Timer::Timer(double* _duration)
{
	m_duration = _duration;
	m_startTime = std::chrono::steady_clock::now();
}

Timer::~Timer()
{
	EndTimer();
}

void Timer::EndTimer() const
{
	const auto endTime = std::chrono::steady_clock::now();
	*m_duration = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_startTime).count()) / 1000000;
}

