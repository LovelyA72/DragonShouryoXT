#pragma once

namespace dsr {
	const std::string OUT_EVENT = "df::out";
	class EventOut : public Event {
	private:

	public:
		__declspec(dllexport) EventOut();
	};
}