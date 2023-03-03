#include "Vector2D.h"
#include "DsrBox.h"

namespace dsr {
	DsrBox::DsrBox(Vector2D loc, float l, float h)
	{
		m_location = loc;
		m_length = l;
		m_height = h;
	}
	Vector2D DsrBox::getLocation()
	{
		return m_location;
	}
	float DsrBox::getLength()
	{
		return m_length;
	}
	float DsrBox::getHeight()
	{
		return m_height;
	}
}
