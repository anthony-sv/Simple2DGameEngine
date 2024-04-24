#pragma once
#include <SFML/Graphics.hpp>

#include "Vector2D.hpp"

namespace SGE2D::Animation
{
	class Animation
	{
	public:
		void update();
		void hasEnded();
		std::string& getName();
		Math::Vector2D& getSize();
		sf::Sprite& getSprite();
	private:
		sf::Sprite m_sprite;
		int m_frameCount;
		int m_currentFrame;
		int m_speed;
		Math::Vector2D m_size;
		std::string m_name;
	};
}
