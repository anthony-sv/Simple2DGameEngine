#pragma once
#include <SFML/Graphics.hpp>

#include "Vector2D.hpp"

namespace SGE2D::Animation
{
	class Animation
	{
	public:
		void update();
		bool hasEnded() const;
		std::string const& getName() const;
		Math::Vector2D const& getSize() const;
		sf::Sprite& getSprite();
		// default contructor
		[[nodiscard]] Animation() = default;
		[[nodiscard]] Animation(std::string const& name, sf::Texture const& texture);
		[[nodiscard]] Animation(std::string const& name, sf::Texture const& texture, std::size_t frameCount, std::size_t speed);
	private:
		sf::Sprite m_sprite;
		std::size_t m_frameCount{ 1 };
		std::size_t m_currentFrame{ 0 };
		std::size_t m_speed{ 0 };
		Math::Vector2D m_size{ 1,1 }; // size of the animation frame
		std::string m_name{ "NONE" };
	};
}