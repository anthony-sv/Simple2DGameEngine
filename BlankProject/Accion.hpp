#pragma once
#include <string>

namespace MVS2D
{
	class Accion
	{
	public:
		[[nodiscard]] Accion() = default;
		[[nodiscard]] Accion(std::string const& nombre, std::string const& tipo);

		std::string const& obtenerNombre() const;
		std::string const& obtenerTipo() const;
	private:
		std::string m_nombre{ "N/A" };
		std::string m_tipo{ "N/A" };

	};
}