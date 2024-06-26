#include "Vector2D.hpp"
#include <cmath>
#include <format>
#include <limits>

namespace MVS2D::Matematicas
{
	Vector2D::Vector2D()
		: Vector2D{ 0.0f,0.0f }
	{}

	Vector2D::Vector2D(
		float const x,
		float const y)
		: x{ x },
		y{ y }
	{}

	bool
		Vector2D::operator ==(
			Vector2D const& otro) const
	{
		constexpr float epsilon = std::numeric_limits<float>::epsilon();
		return std::abs(x - otro.x) <= epsilon * std::abs(x + otro.x) &&
			std::abs(y - otro.y) <= epsilon * std::abs(y + otro.y);
	}

	bool
		Vector2D::operator !=(
			Vector2D const& otro) const
	{
		return !(*this == otro);
	}

	Vector2D
		Vector2D::operator +(
			Vector2D const& otro) const
	{
		return { x + otro.x, y + otro.y };
	}

	Vector2D
		Vector2D::operator -(
			Vector2D const& otro) const
	{
		return { x - otro.x, y - otro.y };
	}

	Vector2D
		Vector2D::operator *(
			float const escalar) const
	{
		return { x * escalar, y * escalar };
	}

	Vector2D
		Vector2D::operator /(
			float const escalar) const
	{
		return { x / escalar, y / escalar };
	}

	void
		Vector2D::operator+=(
			Vector2D const& otro)
	{
		x += otro.x;
		y += otro.y;
	}

	void
		Vector2D::operator-=(
			Vector2D const& otro)
	{
		x -= otro.x;
		y -= otro.y;
	}

	void
		Vector2D::operator*=(
			float const escalar)
	{
		x *= escalar;
		y *= escalar;
	}

	void
		Vector2D::operator/=(
			float const escalar)
	{
		x /= escalar;
		y /= escalar;
	}

	float
		Vector2D::longitud() const
	{
		return std::sqrt(x * x + y * y);
	}

	float
		Vector2D::distancia(
			Vector2D const& otro) const
	{
		return (otro - *this).longitud();
	}

	Vector2D
		Vector2D::normalizar() const
	{
		float const longitud = this->longitud();
		return { x / longitud, y / longitud };
	}
}

std::ostream&
MVS2D::Matematicas::operator<<(
	std::ostream& flujoSalida,
	Vector2D const& vector)
{
	flujoSalida << "Vector2D(" << vector.x << ", " << vector.y << ")";
	return flujoSalida;
}