#pragma once
#include "Vector2D.h"

namespace dsr {
	class Box {
	private:
		Vector2D m_location;
		float m_length;
		float m_height;
	public:
		__declspec(dllexport) Box(Vector2D loc,float l,float h);
		Vector2D __declspec(dllexport) getLocation();
		void __declspec(dllexport) setLocation(Vector2D vec);
		float __declspec(dllexport) getLength();
		void __declspec(dllexport) setLength(float f);
		float __declspec(dllexport) getHeight();
		void __declspec(dllexport) setHeight(float f);
	};
}