#include "CajaDelimitadora.hpp"

MVS2D::Matematicas::Vector2D MVS2D::Fisica::CajaDelimitadora::calcularSuperposicion(std::shared_ptr<Entidades::Entidad> a,
                                                                   std::shared_ptr<Entidades::Entidad> b)
{
	if (a->cColisionCajaDelimitadora && a->cMovimiento && b->cColisionCajaDelimitadora && b->cMovimiento)
	{
		MVS2D::Matematicas::Vector2D const aPosition = a->cMovimiento->posicion;
		MVS2D::Matematicas::Vector2D const bPosition = b->cMovimiento->posicion;
		MVS2D::Matematicas::Vector2D const ahalfSize = a->cColisionCajaDelimitadora->mitadTamanio;
		MVS2D::Matematicas::Vector2D const bhalfSize = b->cColisionCajaDelimitadora->mitadTamanio;

		MVS2D::Matematicas::Vector2D const delta{ std::abs(aPosition.x - bPosition.x), std::abs(aPosition.y - bPosition.y) };
		return ahalfSize + bhalfSize - delta;
	}
	return{ 0,0 };
}

MVS2D::Matematicas::Vector2D MVS2D::Fisica::CajaDelimitadora::calcularSuperposicionAnterior(std::shared_ptr<Entidades::Entidad> a,
	std::shared_ptr<Entidades::Entidad> b)
{
	if (a->cColisionCajaDelimitadora && a->cMovimiento && b->cColisionCajaDelimitadora && b->cMovimiento)
	{
		MVS2D::Matematicas::Vector2D const aPosition = a->cMovimiento->posicionAnterior;
		MVS2D::Matematicas::Vector2D const bPosition = b->cMovimiento->posicionAnterior;
		MVS2D::Matematicas::Vector2D const ahalfSize = a->cColisionCajaDelimitadora->mitadTamanio;
		MVS2D::Matematicas::Vector2D const bhalfSize = b->cColisionCajaDelimitadora->mitadTamanio;

		MVS2D::Matematicas::Vector2D const delta{ std::abs(aPosition.x - bPosition.x), std::abs(aPosition.y - bPosition.y) };
		return ahalfSize + bhalfSize - delta;
	}
	return{ 0,0 };
}