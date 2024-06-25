#pragma once

#include "Componentes.hpp"
#include <memory>
#include <string>

namespace MVS2D::Entidades
{
	class Entidad final
	{
	public:
		Entidad(std::size_t const& identificador, std::string const& etiqueta);
		void destruir();
		[[nodiscard]] std::size_t obtenerIdentificador() const;
		[[nodiscard]] bool estaActiva() const;
		[[nodiscard]] std::string const& obtenerEtiqueta() const;
		std::unique_ptr<Componentes::CMovimiento> cMovimiento;
		std::unique_ptr<Componentes::CEntrada> cEntrada;
		std::unique_ptr<Componentes::CRenderizar> cRenderizar;
		std::unique_ptr<Componentes::CAnimacion> cAnimacion;
		std::unique_ptr<Componentes::CColisionCajaDelimitadora> cColisionCajaDelimitadora;
		std::unique_ptr<Componentes::CGravedad> cGravedad;
		std::unique_ptr<Componentes::CEstado> cEstado;
	private:
		bool m_activa{ true };
		std::size_t m_identificador{ 0 };
		std::string m_etiqueta{ "N/A" };
	};
}