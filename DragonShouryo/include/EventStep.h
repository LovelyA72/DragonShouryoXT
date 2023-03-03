#pragma once
///
/// A "step" event, generated once per game loop.
///

#include "Event.h"

namespace dsr {

	const std::string STEP_EVENT = "df::step";

	class EventStep : public Event {

	private:
		int m_step_count;  /// Iteration number of game loop.

	public:
		/// Default constructor.
		__declspec(dllexport) EventStep();

		/// Constructor with initial step count.
		__declspec(dllexport) EventStep(int init_step_count);

		/// Set step count.
		__declspec(dllexport) void setStepCount(int new_step_count);

		/// Get step count.
		__declspec(dllexport) int getStepCount() const;
	};

} // end of namespace dsr
