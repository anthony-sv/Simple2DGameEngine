#include "Accion.hpp"

MVS2D::Accion::Accion(
	std::string const& nombre,
	std::string const& tipo)
	: m_nombre{ nombre }, m_tipo{ tipo }
{
}

std::string const&
MVS2D::Accion::obtenerNombre() const
{
	return m_nombre;
}

std::string const&
MVS2D::Accion::obtenerTipo() const
{
	return m_tipo;
}