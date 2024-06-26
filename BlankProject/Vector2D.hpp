#pragma once
#include <ostream>
#include <format>
#include <string>

namespace MVS2D::Matematicas
{
	struct [[nodiscard]] Vector2D final
	{
		[[nodiscard]] Vector2D();
		[[nodiscard]] Vector2D(float x, float y);
		float x{}, y{};
		bool operator ==(Vector2D const& otro) const;
		bool operator !=(Vector2D const& otro) const;
		[[nodiscard]] Vector2D operator +(Vector2D const& otro) const;
		[[nodiscard]] Vector2D operator -(Vector2D const& otro) const;
		[[nodiscard]] Vector2D operator *(float escalar) const;
		[[nodiscard]] Vector2D operator /(float escalar) const;
		void operator +=(Vector2D const& otro);
		void operator -=(Vector2D const& otro);
		void operator *=(float const escalar);
		void operator /=(float const escalar);
		[[nodiscard]] float longitud() const;
		[[nodiscard]] float distancia(Vector2D const& otro) const;
		[[nodiscard]] Vector2D normalizar() const;
		friend std::ostream& operator<<(std::ostream& flujoSalida, Vector2D const& vector);
	};
}

template <>
struct std::formatter<MVS2D::Matematicas::Vector2D> : std::formatter<std::string> {
	auto format(MVS2D::Matematicas::Vector2D const& v, std::format_context& ctx) const {
		return std::formatter<std::string>::format(std::format("Vector2D={{X={}, Y={}}}", v.x, v.y), ctx);
	}
};