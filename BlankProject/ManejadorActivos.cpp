#include "ManejadorActivos.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <print>

using namespace MVS2D::Sistemas;

void
MVS2D::Activos::ManejadorActivos::agregarTextura(
	std::string const& nombre,
	std::string const& ruta)
{
	sf::Texture textura;
	textura.loadFromFile(ruta);
	m_texturas[nombre] = textura;
}

void
MVS2D::Activos::ManejadorActivos::agregarFuente(
	std::string const& nombre,
	std::string const& ruta)
{
	m_fuentes[nombre] = sf::Font();
	if (!m_fuentes[nombre].loadFromFile(ruta))
	{
		std::println(std::cerr, "No se ha podido cargar la fuente de la ruta: {}", ruta);
	}
}

void
MVS2D::Activos::ManejadorActivos::agregarAnimacion(
	std::string const& nombre,
	Animaciones::AnimacionSprite const& ruta)
{
	m_animaciones[nombre] = ruta;
}

sf::Texture const&
MVS2D::Activos::ManejadorActivos::obtenerTextura(
	std::string const& nombre) const
{
	return m_texturas.at(nombre);
}

sf::Font const&
MVS2D::Activos::ManejadorActivos::obtenerFuente(
	std::string const& nombre) const
{
	return m_fuentes.at(nombre);

}

Animaciones::AnimacionSprite const&
MVS2D::Activos::ManejadorActivos::obtenerAnimacion(
	std::string const& nombre) const
{
	return m_animaciones.at(nombre);
}

void
MVS2D::Activos::ManejadorActivos::cargarDesdeArchivo(
	std::string const& ruta)
{
	std::ifstream archivoActivos{ ruta };
	if (!archivoActivos) {
		std::println(std::cerr, "No se puede cargar el archivo: {}", ruta);
		std::quick_exit(-1);
	}

	std::string tipoActivo;
	while (archivoActivos >> tipoActivo)
	{
		std::string nombre;
		std::string rutaActivo;
		if (tipoActivo == "Textura")
		{
			archivoActivos >> nombre >> rutaActivo;
			agregarTextura(nombre, rutaActivo);
		}
		else if (tipoActivo == "Animacion")
		{
			int frames, speed;
			archivoActivos >> nombre >> rutaActivo >> frames >> speed;
			sf::Texture const& tex = obtenerTextura(rutaActivo);
			agregarAnimacion(
				nombre,
				Animaciones::AnimacionSprite{ nombre, tex, static_cast<std::size_t>(frames), static_cast<std::size_t>(speed) });
		}
		else if (tipoActivo == "Fuente")
		{
			archivoActivos >> nombre >> rutaActivo;
			agregarFuente(nombre, rutaActivo);
		}
		else
		{
			std::println(std::cerr, "Tipo de activo incorrecto: {}", tipoActivo);
			std::quick_exit(-1);
		}
	}
}