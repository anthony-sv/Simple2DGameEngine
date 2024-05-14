#include "Animation.hpp"
#include <cmath>

// updates the animation to show the next frame, depending on the speed
// animation loopes when it reaches the end
void SGE2D::Animation::Animation::update()
{
	// add the speed to the current frame
	m_currentFrame++;

	// TODO: 1) calculate the correct frame of animation to play based on currentFrame and speed
	//       2) set the texture rectangle properly (see constructor for reference)
}

bool SGE2D::Animation::Animation::hasEnded() const
{
	//return m_currentFrame == m_frameCount;
	// TODO: detect when animation has ended(last frame has been played) and return true
	return false;
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
	: m_sprite{ texture }, m_frameCount{ frameCount }, m_speed{ speed }, m_name{ name }
{
	m_size = { static_cast<float>(texture.getSize().x) / frameCount, static_cast<float>(texture.getSize().y) };
	m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
	m_sprite.setTextureRect(sf::IntRect{ std::floor{m_currentFrame} *m_size.x, 0, static_cast<int>(m_size.x), static_cast<int>(m_size.y) });
}
