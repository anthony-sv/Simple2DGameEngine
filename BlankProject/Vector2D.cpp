#include "Vector2D.hpp"
#include <cmath>
#include <format>

namespace SGE2D::Math
{
	Vector2D::Vector2D() : Vector2D{ 0,0 } {}

	Vector2D::Vector2D(double const x, double const y) : m_x{ x }, m_y{ y } {}

	double Vector2D::getX() const
	{
		return m_x;
	}

	void Vector2D::setX(double const x)
	{
		m_x = x;
	}

	double Vector2D::getY() const
	{
		return m_y;
	}

	void Vector2D::setY(double const y)
	{
		m_y = y;
	}

	bool Vector2D::operator ==(Vector2D const& other) const
	{
		return m_x == other.m_x && m_y == other.m_y;
	}

	bool Vector2D::operator !=(Vector2D const& other) const
	{
		return !(*this == other);
	}

	Vector2D Vector2D::operator +(Vector2D const& other) const
	{
		return { m_x + other.m_x, m_y + other.m_y };
	}

	Vector2D Vector2D::operator -(Vector2D const& other) const
	{
		return { m_x - other.m_x, m_y - other.m_y };
	}

	Vector2D Vector2D::operator *(double const s) const
	{
		return { m_x * s, m_y * s };
	}

	Vector2D Vector2D::operator /(double const s) const
	{
		return { m_x / s, m_y / s };
	}

	double Vector2D::length() const
	{
		return std::sqrt(m_x * m_x + m_y * m_y);
	}

	double Vector2D::distance(Vector2D const& other) const
	{
		return (other - *this).length();
	}

	Vector2D Vector2D::normalize() const
	{
		double const len = length();
		return { m_x / len, m_y / len };
	}
}

std::ostream& SGE2D::Math::operator<<(std::ostream& os, Vector2D const& vec)
{
	os << "Vector2D(" << vec.m_x << ", " << vec.m_y << ")";
	return os;
}
