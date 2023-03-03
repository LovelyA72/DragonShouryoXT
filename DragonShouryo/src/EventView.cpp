#include "EventView.h"

namespace dsr {
	EventView::EventView()
	{
		setType(VIEW_EVENT);
	}
	EventView::EventView(int new_id, float new_value, bool new_delta)
	{
		setType(VIEW_EVENT);
		m_id = new_id;
		m_value = new_value;
		m_delta = new_delta;
	}
	void EventView::setTargetId(int new_id)
	{
		m_id = new_id;
	}
	int EventView::getTargetId() const
	{
		return m_id;
	}
	void EventView::setValue(float new_value)
	{
		m_value = new_value;
	}
	int EventView::getValue() const
	{
		return m_value;
	}
	void EventView::setDelta(bool new_delta)
	{
		m_delta = new_delta;
	}
	bool EventView::getDelta() const
	{
		return m_delta;
	}
}