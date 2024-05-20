#include "BoundingBox.hpp"

SGE2D::Math::Vector2D SGE2D::Physics::BoundingBox::getOverlap(std::shared_ptr<Entts::Entity> a,
	std::shared_ptr<Entts::Entity> b)
{
	if (a->cBoundingBox && a->cTransform && b->cBoundingBox && b->cTransform)
	{
		SGE2D::Math::Vector2D const aPosition = a->cTransform->position;
		SGE2D::Math::Vector2D const bPosition = b->cTransform->position;
		SGE2D::Math::Vector2D const ahalfSize = a->cBoundingBox->halfSize;
		SGE2D::Math::Vector2D const bhalfSize = b->cBoundingBox->halfSize;

		SGE2D::Math::Vector2D const delta{ std::abs(aPosition.x - bPosition.x), std::abs(aPosition.y - bPosition.y) };
		return ahalfSize + bhalfSize - delta;
	}
	return{ 0,0 };
}

SGE2D::Math::Vector2D SGE2D::Physics::BoundingBox::getPreviousOverlap(std::shared_ptr<Entts::Entity> a,
	std::shared_ptr<Entts::Entity> b)
{
	if (a->cBoundingBox && a->cTransform && b->cBoundingBox && b->cTransform)
	{
		SGE2D::Math::Vector2D const aPosition = a->cTransform->previousPosition;
		SGE2D::Math::Vector2D const bPosition = b->cTransform->previousPosition;
		SGE2D::Math::Vector2D const ahalfSize = a->cBoundingBox->halfSize;
		SGE2D::Math::Vector2D const bhalfSize = b->cBoundingBox->halfSize;

		SGE2D::Math::Vector2D const delta{ std::abs(aPosition.x - bPosition.x), std::abs(aPosition.y - bPosition.y) };
		return ahalfSize + bhalfSize - delta;
	}
	return{ 0,0 };
}