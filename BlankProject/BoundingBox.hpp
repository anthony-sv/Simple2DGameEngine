#pragma once

#include "Entity.hpp"
#include "Vector2D.hpp"

namespace SGE2D::Physics
{
	class BoundingBox
	{
	public:
		static Math::Vector2D getOverlap(std::shared_ptr<Entts::Entity> a, std::shared_ptr<Entts::Entity> b);
		static Math::Vector2D getPreviousOverlap(std::shared_ptr<Entts::Entity> a, std::shared_ptr<Entts::Entity> b);
	};
}