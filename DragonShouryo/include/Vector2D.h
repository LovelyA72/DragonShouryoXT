#pragma once
///
/// A 2d (x,y) vector
///

#include <string>

namespace dsr {

	class Vector2D {

	private:
		float m_x; 			///< Horizontal component.
		float m_y; 			///< Vertical component.

	public:

		/// Create Vector with (x,y).  
		__declspec(dllexport) Vector2D(float init_x, float init_y);

		/// Default is (0,0).
		__declspec(dllexport) Vector2D();

		__declspec(dllexport) float getX() const;		    ///< Get horizontal component.
		__declspec(dllexport) void setX(float new_x);	    ///< Set horizontal component.
		__declspec(dllexport) float getY()const;		    ///< Get vertical component.
		__declspec(dllexport) void setY(float new_y);	    ///< Set vertical component.
		__declspec(dllexport) void setXY(float new_x, float new_y); ///< Set horizizontal & vertical.
		__declspec(dllexport) void normalize();			///< Normalize vector.
		__declspec(dllexport) void scale(float s);		///< Scale vector.
		__declspec(dllexport) float getMagnitude() const;	///< Return magnitude.
		__declspec(dllexport) bool operator==(const Vector2D& other) const;  ///< Compare Vector.
		__declspec(dllexport) bool operator!=(const Vector2D& other) const;  ///< Compare Vector.
		__declspec(dllexport) Vector2D& operator+=(const Vector2D& other); ///< Add other Vector to this one.
		__declspec(dllexport) Vector2D& operator-=(const Vector2D& other); ///< Minus other Vector to this one.
		__declspec(dllexport) Vector2D operator+(const Vector2D& other) const; ///< Add Vector.
		__declspec(dllexport) Vector2D operator-(const Vector2D& other) const; ///< Subtract Vector.
		__declspec(dllexport) Vector2D operator*(const float other) const; ///< Add Vector.
		__declspec(dllexport) bool operator!() const;		       ///< Test if (0,0).
		__declspec(dllexport) std::string toString() const; ///< Return attributes as string.
	};

} // end of namespace df