#include "BoundingBox.hpp"

SGE2D::Math::Vector2D SGE2D::Physics::BoundingBox::getOverlap(std::shared_ptr<Entts::Entity> a,
	std::shared_ptr<Entts::Entity> b)
{
	// TODO: return the overlap rectangle size of the bounding boxes of the two entities
	return{ 0,0 };
}

SGE2D::Math::Vector2D SGE2D::Physics::BoundingBox::getPreviousOverlap(std::shared_ptr<Entts::Entity> a,
	std::shared_ptr<Entts::Entity> b)
{
	// TODO: return the previous overlap rectangle size of the bounding boxes of the two entities
	//       previous overlap uses the entities' previous positions
	return{ 0,0 };
}
