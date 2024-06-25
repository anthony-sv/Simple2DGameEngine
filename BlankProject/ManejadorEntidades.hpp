#pragma once
#include "Entidad.hpp"
#include <vector>
#include <unordered_map>

namespace MVS2D::Entidades
{
	using VectorEntidades = std::vector<std::shared_ptr<Entidad>>;
	using MapaEntidades = std::unordered_map<std::string, VectorEntidades>;

	class [[nodiscard]] ManejadorEntidades final
	{
	public:
		[[nodiscard]] ManejadorEntidades();
		void actualizar();
		std::shared_ptr<Entidad> agregarEntidad(std::string const& etiqueta);
		[[nodiscard]] VectorEntidades const& obtenerEntidades() const;
		[[nodiscard]] VectorEntidades const& obtenerEntidades(std::string const& etiqueta) const;
		[[nodiscard]] MapaEntidades const& obtenerMapaEntidades() const;
	private:
		static void eliminarEntidades(VectorEntidades& vector);
		VectorEntidades m_entidades{};
		MapaEntidades m_mapaEntidades{};
		VectorEntidades m_porAgregar{};
		std::size_t m_totalEntidades{ 0 };
	};
};