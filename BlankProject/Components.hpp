#pragma once
#include "Vector2D.hpp"
#include <SFML/Graphics.hpp>

namespace SGE2D::Components
{
	struct IComponent
	{
		bool has = false;
	};

	struct CTransform : IComponent
	{
		SGE2D::Math::Vector2D position{ 0.0f, 0.0f };
		SGE2D::Math::Vector2D previousPosition{ 0.0f, 0.0f };
		SGE2D::Math::Vector2D scale{ 1.0f, 1.0f };
		SGE2D::Math::Vector2D velocity{ 0.0f, 0.0f };
		float m_rotationAngle{ 0.0f };

		CTransform() = default;
		CTransform(SGE2D::Math::Vector2D const& p)
			: position{ p }
		{}
		CTransform(SGE2D::Math::Vector2D const& p, SGE2D::Math::Vector2D const& v, SGE2D::Math::Vector2D const& s, float const angle)
			: position{ p }, scale{ s }, velocity{ v }, m_rotationAngle{ angle }
		{}

	};

	struct CShape : IComponent
	{
		sf::CircleShape circleShape;
		CShape() = default;
		CShape(float const radius, std::size_t const& points, sf::Color const& fill, sf::Color const& outline, float const thickness)
			: circleShape{ radius, points }
		{
			circleShape.setFillColor(fill);
			circleShape.setOutlineColor(outline);
			circleShape.setOutlineThickness(thickness);
			circleShape.setOrigin(radius, radius);
		}
	};

	struct CInput : IComponent
	{
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		CInput() = default;
	};
}