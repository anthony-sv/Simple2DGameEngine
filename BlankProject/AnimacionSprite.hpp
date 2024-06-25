#pragma once
#include <SFML/Graphics.hpp>

#include "Vector2D.hpp"

namespace MVS2D::Sistemas::Animaciones
{
	class AnimacionSprite
	{
	public:
		void actualizar();
		bool finalizo() const;
		std::string const& obtenerNombre() const;
		Matematicas::Vector2D const& obtenerTamanio() const;
		sf::Sprite& obtenerSprite();
		[[nodiscard]] AnimacionSprite() = default;
		[[nodiscard]] AnimacionSprite(std::string const& nombre, sf::Texture const& textura);
		[[nodiscard]] AnimacionSprite(std::string const& nombre, sf::Texture const& textura, std::size_t numeroFrames, std::size_t velocidad);
	private:
		sf::Sprite m_sprite;
		std::size_t m_numeroFrames{ 1 };
		std::size_t m_frameActual{ 0 };
		std::size_t m_velocidad{ 0 };
		Matematicas::Vector2D m_tamanio{ 1,1 };
		std::string m_nombre{ "N/A" };
	};
}