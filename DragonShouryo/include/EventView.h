#pragma once
#include "Event.h"

namespace dsr {
	const std::string VIEW_EVENT = "df-view";

	class EventView : public Event {
	private:
		int m_id;
		bool m_delta;
		float m_value;
	public:
		/// Create view event with tag VIEW_EVENT, value 0 and delta false.
		__declspec(dllexport) EventView();

		/// Create view event with tag, value and delta as indicated.
		__declspec(dllexport) EventView(int new_id, float new_value, bool new_delta);

		/// Set tag to new tag.
		__declspec(dllexport) void setTargetId(int new_id);

		/// Get tag.
		__declspec(dllexport) int getTargetId() const;

		/// Set value to new value.
		__declspec(dllexport) void setValue(float new_value);

		/// Get value.
		__declspec(dllexport) int getValue() const;

		/// Set delta to new delta.
		__declspec(dllexport) void setDelta(bool new_delta);

		/// Get delta.
		__declspec(dllexport) bool getDelta() const;
	};
}