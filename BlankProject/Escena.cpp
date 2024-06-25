#include "Escena.hpp"

MVS2D::Escenas::Escena::Escena(MotorVideojuegos* motorVideojuegos)
	: m_juego{ motorVideojuegos }
{
}

void MVS2D::Escenas::Escena::realizarAccion(Accion const& accion)
{
	sRealizarAccion(accion);
}

void MVS2D::Escenas::Escena::registrarAccion(int const teclaEntrada, std::string const& nombre)
{
	m_acciones[teclaEntrada] = nombre;
}

std::size_t MVS2D::Escenas::Escena::obtenerFrameActual() const
{
	return m_frameActual;
}

bool MVS2D::Escenas::Escena::finalizo() const
{
	return m_finalizo;
}

std::size_t MVS2D::Escenas::Escena::obtenerAnchoVentana() const
{
	return m_juego->obtenerVentana().getSize().x;
}

std::size_t MVS2D::Escenas::Escena::obtenerAltoVentana() const
{
	return m_juego->obtenerVentana().getSize().y;
}

void MVS2D::Escenas::Escena::ponerPausa(bool const pausa)
{
	m_pausado = pausa;
}

std::unordered_map<int, std::string> const& MVS2D::Escenas::Escena::obtenerMapaAcciones() const
{
	return m_acciones;
}