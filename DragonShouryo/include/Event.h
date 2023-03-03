#pragma once
///
/// The base event
///
// System includes.
#include <string>

namespace dsr {

	const std::string UNDEFINED_EVENT = "df::undefined";

	class Event {

	private:
		std::string m_event_type;    ///< Holds event type.

	public:
		/// Create base event.
		__declspec(dllexport) Event();

		/// Destructor.
		__declspec(dllexport) virtual ~Event();

		/// Set event type.
		__declspec(dllexport) void setType(std::string new_type);

		/// Get event type.
		__declspec(dllexport) std::string getType() const;
	};

} // end of namespace dsr