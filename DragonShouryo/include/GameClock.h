#pragma once
#include <Windows.h>
#include <chrono>
///
/// The clock, for timing
///

namespace dsr {

	class GameClock {

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

	public:
		/// Sets previous_time to current time.
		__declspec(dllexport) GameClock();

		/// Return time elapsed since delta() was called, -1 if error.
		/// Resets clock time.
		/// Units are microseconds.
		__declspec(dllexport) long int delta();

		/// Return time elapsed since delta() was called, -1 if error.
		/// Does not reset clock time.
		/// Units are microseconds.
		__declspec(dllexport) long int split() const;
	};

} // end of namespace dsr
