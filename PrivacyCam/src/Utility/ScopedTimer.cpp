#include "ScopedTimer.h"

using namespace pricam;

ScopedTimer::ScopedTimer(double* _duration) :
	m_startTime(std::chrono::steady_clock::now()),
	m_duration(_duration),
	m_timingFinished(false)
{
}

ScopedTimer::~ScopedTimer()
{
	if (!m_timingFinished)
	{
		EndTimer();
	}
}

void ScopedTimer::EndTimer()
{
	const auto endTime = std::chrono::steady_clock::now();
	*m_duration = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_startTime).count()) / 1000000;
	m_timingFinished = true;
}

