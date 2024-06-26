#include "ManejadorEntidades.hpp"

#include <ranges>
#include <print>

namespace MVS2D::Entidades
{
	ManejadorEntidades::ManejadorEntidades() = default;

	void
		ManejadorEntidades::actualizar()
	{
		for (auto const& entidad : m_porAgregar)
		{
			m_entidades.push_back(entidad);
			m_mapaEntidades[entidad->obtenerEtiqueta()].push_back(entidad);
		}
		eliminarEntidades(m_entidades);
		for (auto& vectorEntidades : m_mapaEntidades | std::views::values)
		{
			eliminarEntidades(vectorEntidades);
		}
		m_porAgregar.clear();
	}

	void
		ManejadorEntidades::eliminarEntidades(
			VectorEntidades& vector)
	{
		std::erase_if(vector, [](auto const& entidad) { return !entidad->estaActiva(); });
	}

	std::shared_ptr<Entidad>
		ManejadorEntidades::agregarEntidad(
			std::string const& etiqueta)
	{
		auto entidad = std::make_shared<Entidad>(m_totalEntidades++, etiqueta);
		m_porAgregar.push_back(entidad);
		return entidad;
	}

	VectorEntidades const&
		ManejadorEntidades::obtenerEntidades() const
	{
		return m_entidades;
	}

	VectorEntidades const&
		ManejadorEntidades::obtenerEntidades(
			std::string const& etiqueta) const
	{
		return m_mapaEntidades.at(etiqueta);
	}

	std::unordered_map<std::string, VectorEntidades> const&
		ManejadorEntidades::obtenerMapaEntidades() const
	{
		return m_mapaEntidades;
	}
}