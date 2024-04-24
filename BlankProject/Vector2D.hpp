#pragma once
#include <ostream>
#include <format>
#include <string>

namespace SGE2D::Math
{
	struct [[nodiscard]] Vector2D final
	{
		[[nodiscard]] Vector2D();
		[[nodiscard]] Vector2D(float x, float y);
		float x{}, y{};
		bool operator ==(Vector2D const& other) const;
		bool operator !=(Vector2D const& other) const;
		[[nodiscard]] Vector2D operator +(Vector2D const& other) const;
		[[nodiscard]] Vector2D operator -(Vector2D const& other) const;
		[[nodiscard]] Vector2D operator *(float s) const;
		[[nodiscard]] Vector2D operator /(float s) const;
		void operator +=(Vector2D const& other);
		void operator -=(Vector2D const& other);
		void operator *=(float const s);
		void operator /=(float const s);
		[[nodiscard]] float length() const;
		[[nodiscard]] float distance(Vector2D const& other) const;
		[[nodiscard]] Vector2D normalize() const;
		friend std::ostream& operator<<(std::ostream& os, Vector2D const& vec);
	};
}

template <>
struct std::formatter<SGE2D::Math::Vector2D> : std::formatter<std::string> {
	auto format(SGE2D::Math::Vector2D const& v, std::format_context& ctx) const {
		return std::formatter<std::string>::format(std::format("Vector2D={{X={}, Y={}}}", v.x, v.y), ctx);
	}
};