#include "EventCollision.h"

namespace dsr {
	EventCollision::EventCollision()
	{
		setType(COLLISION_EVENT);
	}
	EventCollision::EventCollision(DsrObject* p_o1, DsrObject* p_o2, Vector2D p)
	{
		setType(COLLISION_EVENT);
		m_p_obj1 = p_o1;
		m_p_obj2 = p_o2;
		m_pos = p;
	}
	void EventCollision::setObject1(DsrObject* p_new_o1)
	{
		m_p_obj1 = p_new_o1;
	}
	DsrObject* EventCollision::getObject1() const
	{
		return m_p_obj1;
	}
	void EventCollision::setObject2(DsrObject* p_new_o2)
	{
		m_p_obj2 = p_new_o2;
	}
	DsrObject* EventCollision::getObject2() const
	{
		return m_p_obj2;
	}
	void EventCollision::setPosition(Vector2D new_pos)
	{
		m_pos = new_pos;
	}
	Vector2D EventCollision::getPosition() const
	{
		return m_pos;
	}
}