#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "AnimacionSprite.hpp"

namespace MVS2D::Activos // Se cargan al inicio, pero deberia ser al inicio de la escena
{
	class ManejadorActivos
	{
	public:
		void agregarTextura(std::string const& nombre, std::string const& ruta);
		void agregarFuente(std::string const& nombre, std::string const& ruta);
		void agregarAnimacion(std::string const& nombre, Sistemas::Animaciones::AnimacionSprite const& ruta);

		sf::Texture const& obtenerTextura(std::string const& nombre) const;
		sf::Font const& obtenerFuente(std::string const& nombre) const;
		Sistemas::Animaciones::AnimacionSprite const& obtenerAnimacion(std::string const& nombre) const;
		void cargarDesdeArchivo(std::string const& ruta);
	private:
		std::unordered_map<std::string, sf::Texture> m_texturas;
		std::unordered_map<std::string, sf::Font> m_fuentes;
		std::unordered_map<std::string, Sistemas::Animaciones::AnimacionSprite> m_animaciones;
	};
}