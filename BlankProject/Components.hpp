#pragma once
#include "Vector2D.hpp"
#include <SFML/Graphics.hpp>

namespace SGE2D::Components
{
	struct IComponent
	{
		bool has = false;
		virtual ~IComponent() = default;
	};

	struct [[nodiscard]] CTransform final : IComponent
	{
		SGE2D::Math::Vector2D position{ 0.0f, 0.0f };
		SGE2D::Math::Vector2D previousPosition{ 0.0f, 0.0f };
		SGE2D::Math::Vector2D scale{ 1.0f, 1.0f };
		SGE2D::Math::Vector2D velocity{ 0.0f, 0.0f };
		float angle{ 0.0f };

		[[nodiscard]] CTransform() = default;
		explicit [[nodiscard]] CTransform(SGE2D::Math::Vector2D const& position)
			: position{ position }
		{}
		[[nodiscard]] CTransform(SGE2D::Math::Vector2D const& position, SGE2D::Math::Vector2D const& velocity, SGE2D::Math::Vector2D const& scale, float const angle)
			: position{ position }, scale{ scale }, velocity{ velocity }, angle{ angle }
		{}

	};

	struct [[nodiscard]] CCircleShape final : IComponent
	{
		sf::CircleShape circleShape;
		[[nodiscard]] CCircleShape() = default;
		[[nodiscard]] CCircleShape(float const radius, std::size_t const& segments, sf::Color const& fill, sf::Color const& outline, float const thickness)
			: circleShape{ radius, segments }
		{
			circleShape.setFillColor(fill);
			circleShape.setOutlineColor(outline);
			circleShape.setOutlineThickness(thickness);
			circleShape.setOrigin(radius, radius);
		}
	};

	struct [[nodiscard]] CInput final : IComponent
	{
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		[[nodiscard]] CInput() = default;
	};

	struct [[nodiscard]] CCollision final : IComponent
	{
		float radius{ 0.0f };
		explicit [[nodiscard]] CCollision(float radius)
			:radius{ radius } {}
	};

	struct [[nodiscard]] CRender final : IComponent
	{
		bool render{ true };
		explicit [[nodiscard]] CRender(bool const render)
			:render{ render } {}
	};
}