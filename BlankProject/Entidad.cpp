#include "Entidad.hpp"

namespace MVS2D::Entidades
{
	Entidad::Entidad(std::size_t const& identificador, std::string const& etiqueta)
		: m_identificador{ identificador }, m_etiqueta{ etiqueta }
	{}

	void Entidad::destruir()
	{
		m_activa = false;
	}

	std::size_t Entidad::obtenerIdentificador() const
	{
		return m_identificador;
	}

	bool Entidad::estaActiva() const
	{
		return m_activa;
	}

	std::string const& Entidad::obtenerEtiqueta() const
	{
		return m_etiqueta;
	}
}