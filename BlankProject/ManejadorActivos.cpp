#include "ManejadorActivos.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <print>

using namespace MVS2D::Sistemas;

void MVS2D::Activos::ManejadorActivos::agregarTextura(std::string const& nombre, std::string const& ruta)
{
	sf::Texture texture;
	texture.loadFromFile(ruta);
	m_texturas[nombre] = texture;
}

void MVS2D::Activos::ManejadorActivos::agregarFuente(std::string const& nombre, std::string const& ruta)
{
	m_fuentes[nombre] = sf::Font();
	if (!m_fuentes[nombre].loadFromFile(ruta))
	{
		std::println(std::cerr, "Could not load Font from {}", ruta);
	}
}

void MVS2D::Activos::ManejadorActivos::agregarAnimacion(std::string const& nombre, Animaciones::AnimacionSprite const& ruta)
{
	m_animaciones[nombre] = ruta;
}

sf::Texture const& MVS2D::Activos::ManejadorActivos::obtenerTextura(std::string const& nombre) const
{
	return m_texturas.at(nombre);
}

sf::Font const& MVS2D::Activos::ManejadorActivos::obtenerFuente(std::string const& nombre) const
{
	return m_fuentes.at(nombre);

}

Animaciones::AnimacionSprite const& MVS2D::Activos::ManejadorActivos::obtenerAnimacion(std::string const& nombre) const
{
	return m_animaciones.at(nombre);
}

void MVS2D::Activos::ManejadorActivos::cargarDesdeArchivo(std::string const& ruta)
{
	std::ifstream file(ruta);
	if (!file) {
		std::println(std::cerr, "Could not load {} file!", ruta);
		std::quick_exit(-1);
	}

	std::string assetType;
	while (file >> assetType)
	{
		std::string name;
		std::string assetPath;
		if (assetType == "Texture")
		{
			file >> name >> assetPath;
			agregarTextura(name, assetPath);
		}
		else if (assetType == "Animation")
		{
			int frames, speed;
			file >> name >> assetPath >> frames >> speed;
			sf::Texture const& tex = obtenerTextura(assetPath);
			agregarAnimacion(name, Animaciones::AnimacionSprite{ name, tex, static_cast<std::size_t>(frames), static_cast<std::size_t>(speed) });
		}
		else if (assetType == "Font")
		{
			file >> name >> assetPath;
			agregarFuente(name, assetPath);
		}
		else
		{
			std::println(std::cerr, "Incorrect asset type: {}", assetType);
			std::quick_exit(-1);
		}
	}
}