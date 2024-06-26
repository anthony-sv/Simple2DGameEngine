#include "CajaDelimitadora.hpp"

MVS2D::Matematicas::Vector2D
MVS2D::Fisica::CajaDelimitadora::calcularSuperposicion(
	std::shared_ptr<Entidades::Entidad> a,
	std::shared_ptr<Entidades::Entidad> b)
{
	if (a->cColisionCajaDelimitadora && a->cMovimiento && b->cColisionCajaDelimitadora && b->cMovimiento)
	{
		Matematicas::Vector2D const aPosicion = a->cMovimiento->posicion;
		Matematicas::Vector2D const bPosicion = b->cMovimiento->posicion;
		Matematicas::Vector2D const aMitadTamanio = a->cColisionCajaDelimitadora->mitadTamanio;
		Matematicas::Vector2D const bMitadTamanio = b->cColisionCajaDelimitadora->mitadTamanio;

		Matematicas::Vector2D const delta{ std::abs(aPosicion.x - bPosicion.x), std::abs(aPosicion.y - bPosicion.y) };
		return aMitadTamanio + bMitadTamanio - delta;
	}
	return{ 0,0 };
}

MVS2D::Matematicas::Vector2D
MVS2D::Fisica::CajaDelimitadora::calcularSuperposicionAnterior(
	std::shared_ptr<Entidades::Entidad> a,
	std::shared_ptr<Entidades::Entidad> b)
{
	if (a->cColisionCajaDelimitadora && a->cMovimiento && b->cColisionCajaDelimitadora && b->cMovimiento)
	{
		Matematicas::Vector2D const aPosicionAnterior = a->cMovimiento->posicionAnterior;
		Matematicas::Vector2D const bPosicionAnterior = b->cMovimiento->posicionAnterior;
		Matematicas::Vector2D const aMitadTamanio = a->cColisionCajaDelimitadora->mitadTamanio;
		Matematicas::Vector2D const bMitadTamanio = b->cColisionCajaDelimitadora->mitadTamanio;

		Matematicas::Vector2D const delta{
			std::abs(aPosicionAnterior.x - bPosicionAnterior.x),
			std::abs(aPosicionAnterior.y - bPosicionAnterior.y) };
		return aMitadTamanio + bMitadTamanio - delta;
	}
	return{ 0,0 };
}