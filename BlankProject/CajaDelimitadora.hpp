#pragma once

#include "Entidad.hpp"
#include "Vector2D.hpp"

namespace MVS2D::Fisica
{
	class CajaDelimitadora
	{
	public:
		static Matematicas::Vector2D calcularSuperposicion(std::shared_ptr<Entidades::Entidad> a, std::shared_ptr<Entidades::Entidad> b);
		static Matematicas::Vector2D calcularSuperposicionAnterior(std::shared_ptr<Entidades::Entidad> a, std::shared_ptr<Entidades::Entidad> b);
	};
}