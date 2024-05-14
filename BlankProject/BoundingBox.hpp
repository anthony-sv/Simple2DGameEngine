#pragma once

#include "Entity.hpp"
#include "Vector2D.hpp"

namespace SGE2D::Physics
{
	class BoundingBox
	{
	public:
		Math::Vector2D getOverlap(std::shared_ptr<Entts::Entity> a, std::shared_ptr<Entts::Entity> b);
		Math::Vector2D getPreviousOverlap(std::shared_ptr<Entts::Entity> a, std::shared_ptr<Entts::Entity> b);
	private:
	};
}

