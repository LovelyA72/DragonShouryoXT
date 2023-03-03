#pragma once
#include "Event.h"
#include "Vector2D.h"

namespace dsr {

	const std::string MSE_EVENT = "df::mouse";

	/// Set of mouse actions recognized by Dragonfly.
	enum EventMouseAction {
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,
		PRESSED,
		MOVED,
		RELEASED,
	};

	/// Set of mouse buttons recognized by Dragonfly.
	namespace Mouse {
		enum Button {
			UNDEFINED_MOUSE_BUTTON = -1,
			LEFT,
			RIGHT,
			MIDDLE,
		};
	} // end of namespace Mouse

	class EventMouse : public Event {

	private:
		EventMouseAction m_mouse_action;         ///< Mouse action.
		Mouse::Button m_mouse_button;		   ///< Mouse button.
		Vector2D m_mouse_xy;		           ///< Mouse (x,y) coordinates.

	public:
		__declspec(dllexport) EventMouse();

		/// Set mouse event's action.
		__declspec(dllexport) void setMouseAction(EventMouseAction new_mouse_action);

		/// Get mouse event's action.
		__declspec(dllexport) EventMouseAction getMouseAction() const;

		/// Set mouse event's button.
		__declspec(dllexport) void setMouseButton(Mouse::Button new_mouse_button);

		/// Get mouse event's button.
		__declspec(dllexport) Mouse::Button getMouseButton() const;

		/// Set mouse event's position.
		__declspec(dllexport) void setMousePosition(Vector2D new_mouse_xy);

		/// Get mouse event's position.
		__declspec(dllexport) Vector2D getMousePosition() const;
	};

}