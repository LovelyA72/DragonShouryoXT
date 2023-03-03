#pragma once
#include "Vector2D.h"

namespace dsr {
	class DsrBox {
	private:
		Vector2D m_location;
		float m_length;
		float m_height;
	public:
		DsrBox(Vector2D loc,float l,float h);
		Vector2D getLocation();
		float getLength();
		float getHeight();
	};
}