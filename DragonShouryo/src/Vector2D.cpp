#include "Vector2D.h"

namespace dsr {
	Vector2D::Vector2D(float init_x, float init_y)
	{
		m_x = init_x;
		m_y = init_y;
	}
	Vector2D::Vector2D()
	{
		m_x = 0;
		m_y = 0;
	}
	float Vector2D::getX() const
	{
		return m_x;
	}
	void Vector2D::setX(float new_x)
	{
		m_x = new_x;
	}
	float Vector2D::getY() const
	{
		return m_y;
	}
	void Vector2D::setY(float new_y)
	{
		m_y = new_y;
	}
	void Vector2D::setXY(float new_x, float new_y)
	{
		m_x = new_x;
		m_y = new_y;
	}
	void Vector2D::normalize()
	{
		float distance = this->getMagnitude();
		if (distance) {
			m_x = m_x / distance;
			m_y = m_y / distance;
		}
	}
	void Vector2D::scale(float s)
	{
		m_x *= s;
		m_y *= s;
	}
	float Vector2D::getMagnitude() const
	{
		return sqrt(m_x * m_x + m_y * m_y);
	}
	bool Vector2D::operator==(const Vector2D& other) const
	{
		return (other.getX() == m_x) and (other.getY() == m_y);
	}
	bool Vector2D::operator!=(const Vector2D& other) const
	{
		return !((other.getX() == m_x) and (other.getY() == m_y));
	}
	Vector2D& Vector2D::operator+=(const Vector2D& other)
	{
		m_x += other.m_x;
		m_y += other.m_y;
		return *this;
	}
	Vector2D& Vector2D::operator-=(const Vector2D& other)
	{
		m_x -= other.m_x;
		m_y -= other.m_y;
		return *this;
	}
	Vector2D Vector2D::operator+(const Vector2D& other) const
	{
		Vector2D vec(*this);
		return vec += other;
	}
	Vector2D Vector2D::operator-(const Vector2D& other) const
	{
		Vector2D vec(*this);
		return vec -= other;
	}
	Vector2D Vector2D::operator*(const float other) const
	{
		return Vector2D(m_x*other,m_y*other);
	}
	bool Vector2D::operator!() const
	{
		return (m_x == 0 and m_y == 0);
	}
	std::string Vector2D::toString() const
	{
		std::string a = "(";
		std::string b = ",";
		std::string c = ")";
		return a + std::to_string(m_x) + b + std::to_string(m_y) + c;
	}
}


