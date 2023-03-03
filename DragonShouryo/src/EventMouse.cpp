#include "EventMouse.h"

namespace dsr {
	EventMouse::EventMouse()
	{
		setType(MSE_EVENT);
	}
	void EventMouse::setMouseAction(EventMouseAction new_mouse_action)
	{
		m_mouse_action = new_mouse_action;
	}
	EventMouseAction EventMouse::getMouseAction() const
	{
		return m_mouse_action;
	}
	void EventMouse::setMouseButton(Mouse::Button new_mouse_button)
	{
		m_mouse_button = new_mouse_button;
	}
	Mouse::Button EventMouse::getMouseButton() const
	{
		return m_mouse_button;
	}
	void EventMouse::setMousePosition(Vector2D new_mouse_xy)
	{
		m_mouse_xy = new_mouse_xy;
	}
	Vector2D EventMouse::getMousePosition() const
	{
		return m_mouse_xy;
	}
}