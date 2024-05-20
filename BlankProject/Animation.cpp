#include "Animation.hpp"
#include <cmath>

void SGE2D::Animation::Animation::update()
{
	if (m_frameCount < 2)
		return;
	m_currentFrame++;
	std::size_t const frame = (m_currentFrame / m_speed) % m_frameCount;
	m_sprite.setTextureRect(sf::IntRect{ static_cast<int>(std::floor(frame) * m_size.x), 0, static_cast<int>(m_size.x), static_cast<int>(m_size.y) });
}

bool SGE2D::Animation::Animation::hasEnded() const
{
	return (m_currentFrame / m_speed) % m_frameCount == m_frameCount - 1;
}

std::string const& SGE2D::Animation::Animation::getName() const
{
	return m_name;
}

SGE2D::Math::Vector2D const& SGE2D::Animation::Animation::getSize() const
{
	return m_size;
}

sf::Sprite& SGE2D::Animation::Animation::getSprite()
{
	return m_sprite;
}

SGE2D::Animation::Animation::Animation(std::string const& name, sf::Texture const& texture)
	: Animation{ name,texture, 1, 0 }
{
}

SGE2D::Animation::Animation::Animation(std::string const& name, sf::Texture const& texture, std::size_t const frameCount,
	std::size_t const speed)
	: m_frameCount{ frameCount }, m_currentFrame{ 0 }, m_speed{ speed }, m_name{ name }
{
	m_sprite.setTexture(texture);
	m_size = { static_cast<float>(texture.getSize().x) / frameCount, static_cast<float>(texture.getSize().y) };
	m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
	m_sprite.setTextureRect(sf::IntRect{ static_cast<int>(std::floor(m_currentFrame) * m_size.x), 0, static_cast<int>(m_size.x), static_cast<int>(m_size.y) });
}