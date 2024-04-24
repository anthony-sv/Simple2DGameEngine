#include "Entity.hpp"

namespace SGE2D::Entts
{
	Entity::Entity(std::size_t const& id, std::string const& tag)
		: m_id{ id }, m_tag{ tag }
	{}

	void Entity::destroy()
	{
		m_active = false;
	}

	std::size_t Entity::getId() const
	{
		return m_id;
	}

	bool Entity::isActive() const
	{
		return m_active;
	}

	std::string const& Entity::getTag() const
	{
		return m_tag;
	}
}