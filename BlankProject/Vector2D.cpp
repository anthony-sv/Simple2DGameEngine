#include "Vector2D.hpp"
#include <cmath>
#include <format>
#include <limits>

namespace SGE2D::Math
{
	Vector2D::Vector2D() : Vector2D{ 0.0f,0.0f } {}

	Vector2D::Vector2D(float const x, float const y)
		: x{ x }, y{ y }
	{}

	bool Vector2D::operator ==(Vector2D const& other) const
	{
		constexpr float epsilon = std::numeric_limits<float>::epsilon();
		return std::abs(x - other.x) <= epsilon * std::abs(x + other.x) &&
			std::abs(y - other.y) <= epsilon * std::abs(y + other.y);
	}

	bool Vector2D::operator !=(Vector2D const& other) const
	{
		return !(*this == other);
	}

	Vector2D Vector2D::operator +(Vector2D const& other) const
	{
		return { x + other.x, y + other.y };
	}

	Vector2D Vector2D::operator -(Vector2D const& other) const
	{
		return { x - other.x, y - other.y };
	}

	Vector2D Vector2D::operator *(float const s) const
	{
		return { x * s, y * s };
	}

	Vector2D Vector2D::operator /(float const s) const
	{
		return { x / s, y / s };
	}

	void Vector2D::operator+=(Vector2D const& other)
	{
		x += other.x;
		y += other.y;
	}

	void Vector2D::operator-=(Vector2D const& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void Vector2D::operator*=(float const s)
	{
		x *= s;
		y *= s;
	}

	void Vector2D::operator/=(float const s)
	{
		x /= s;
		y /= s;
	}

	float Vector2D::length() const
	{
		return std::sqrt(x * x + y * y);
	}

	float Vector2D::distance(Vector2D const& other) const
	{
		return (other - *this).length();
	}

	Vector2D Vector2D::normalize() const
	{
		float const len = length();
		return { x / len, y / len };
	}
}

std::ostream& SGE2D::Math::operator<<(std::ostream& os, Vector2D const& vec)
{
	os << "Vector2D(" << vec.x << ", " << vec.y << ")";
	return os;
}