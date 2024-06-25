#include "ManejadorEntidades.hpp"

#include <ranges>
#include <print>

namespace MVS2D::Entidades
{
	ManejadorEntidades::ManejadorEntidades() = default;

	void ManejadorEntidades::actualizar()
	{
		for (auto const& entity : m_porAgregar)
		{
			m_entidades.push_back(entity);
			m_mapaEntidades[entity->obtenerEtiqueta()].push_back(entity);
		}
		eliminarEntidades(m_entidades);
		for (auto& entityVec : m_mapaEntidades | std::views::values)
		{
			eliminarEntidades(entityVec);
		}
		m_porAgregar.clear();
	}

	void ManejadorEntidades::eliminarEntidades(VectorEntidades& vector)
	{
		std::erase_if(vector, [](auto const& entity) { return !entity->estaActiva(); });
	}

	std::shared_ptr<Entidad> ManejadorEntidades::agregarEntidad(std::string const& etiqueta)
	{
		auto entity = std::make_shared<Entidad>(m_totalEntidades++, etiqueta);
		m_porAgregar.push_back(entity);
		return entity;
	}

	VectorEntidades const& ManejadorEntidades::obtenerEntidades() const
	{
		return m_entidades;
	}

	VectorEntidades const& ManejadorEntidades::obtenerEntidades(std::string const& etiqueta) const
	{
		return m_mapaEntidades.at(etiqueta);
	}

	std::unordered_map<std::string, VectorEntidades> const& ManejadorEntidades::obtenerMapaEntidades() const
	{
		return m_mapaEntidades;
	}
}