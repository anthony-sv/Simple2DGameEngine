#pragma once
#include <ostream>
#include <format>
#include <string>

namespace SGE2D::Math
{
	class Vector2D
	{
	public:
		Vector2D();
		Vector2D(double x, double y);
		[[nodiscard]] double getX() const;
		void setX(double const x);
		[[nodiscard]] double getY() const;
		void setY(double const y);
		bool operator ==(Vector2D const& other) const;
		bool operator !=(Vector2D const& other) const;
		Vector2D operator +(Vector2D const& other) const;
		Vector2D operator -(Vector2D const& other) const;
		Vector2D operator *(double s) const;
		Vector2D operator /(double s) const;
		[[nodiscard]] double length() const;
		[[nodiscard]] double distance(Vector2D const& other) const;
		[[nodiscard]] Vector2D normalize() const;
		friend std::ostream& operator<<(std::ostream& os, Vector2D const& vec);

	private:
		double m_x{}, m_y{};
	};
}

template <>
struct std::formatter<SGE2D::Math::Vector2D> : std::formatter<std::string> {
	auto format(SGE2D::Math::Vector2D const& v, std::format_context& ctx) const {
		return std::formatter<std::string>::format(std::format("Vector2D={{X={}, Y={}}}", v.getX(), v.getY()), ctx);
	}
};
