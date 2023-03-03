#include <Windows.h>
#include <chrono>
#include "GameClock.h"

namespace dsr {
	GameClock::GameClock()
	{
		m_start = std::chrono::high_resolution_clock::now();
	}
	long int GameClock::delta()
	{
		auto current_time = std::chrono::high_resolution_clock::now();
		auto delta_time = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - m_start);
		m_start = current_time;
		return delta_time.count()*1000;
	}
	long int GameClock::split() const
	{
		auto current_time = std::chrono::high_resolution_clock::now();
		auto delta_time = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - m_start);
		return delta_time.count()*1000;
	}
}