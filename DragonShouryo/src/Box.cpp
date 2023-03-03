#include "Vector2D.h"
#include "Box.h"

namespace dsr {
	Box::Box(Vector2D loc, float l, float h)
	{
		m_location = loc;
		m_length = l;
		m_height = h;
	}
	Vector2D Box::getLocation()
	{
		return m_location;
	}
	void Box::setLocation(Vector2D vec)
	{
		m_location = vec;
	}
	float Box::getLength()
	{
		return m_length;
	}
	void Box::setLength(float f)
	{
		m_length = f;
	}
	float Box::getHeight()
	{
		return m_height;
	}
	void Box::setHeight(float f)
	{
		m_height = f;
	}
}
