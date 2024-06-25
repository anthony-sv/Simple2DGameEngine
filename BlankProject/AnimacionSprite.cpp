#include "AnimacionSprite.hpp"
#include <cmath>

void MVS2D::Sistemas::Animaciones::AnimacionSprite::actualizar()
{
	if (m_numeroFrames < 2)
		return;
	m_frameActual++;
	std::size_t const frame = (m_frameActual / m_velocidad) % m_numeroFrames;
	m_sprite.setTextureRect(sf::IntRect{ static_cast<int>(std::floor(frame) * m_tamanio.x), 0, static_cast<int>(m_tamanio.x), static_cast<int>(m_tamanio.y) });
}

bool MVS2D::Sistemas::Animaciones::AnimacionSprite::finalizo() const
{
	return (m_frameActual / m_velocidad) % m_numeroFrames == m_numeroFrames - 1;
}

std::string const& MVS2D::Sistemas::Animaciones::AnimacionSprite::obtenerNombre() const
{
	return m_nombre;
}

MVS2D::Matematicas::Vector2D const& MVS2D::Sistemas::Animaciones::AnimacionSprite::obtenerTamanio() const
{
	return m_tamanio;
}

sf::Sprite& MVS2D::Sistemas::Animaciones::AnimacionSprite::obtenerSprite()
{
	return m_sprite;
}

MVS2D::Sistemas::Animaciones::AnimacionSprite::AnimacionSprite(std::string const& nombre, sf::Texture const& textura)
	: AnimacionSprite{ nombre,textura, 1, 0 }
{
}

MVS2D::Sistemas::Animaciones::AnimacionSprite::AnimacionSprite(std::string const& nombre, sf::Texture const& textura, std::size_t const numeroFrames,
	std::size_t const velocidad)
	: m_numeroFrames{ numeroFrames }, m_frameActual{ 0 }, m_velocidad{ velocidad }, m_nombre{ nombre }
{
	m_sprite.setTexture(textura);
	m_tamanio = { static_cast<float>(textura.getSize().x) / numeroFrames, static_cast<float>(textura.getSize().y) };
	m_sprite.setOrigin(m_tamanio.x / 2.0f, m_tamanio.y / 2.0f);
	m_sprite.setTextureRect(sf::IntRect{ static_cast<int>(std::floor(m_frameActual) * m_tamanio.x), 0, static_cast<int>(m_tamanio.x), static_cast<int>(m_tamanio.y) });
}