#include "EntityManager.hpp"

#include <ranges>
#include <print>

namespace SGE2D::Entts
{
	EntityManager::EntityManager() = default;

	void EntityManager::update()
	{
		for (auto const& entity : m_toAdd)
		{
			m_entities.push_back(entity);
			m_entityMap[entity->getTag()].push_back(entity);
		}
		removeEntities(m_entities);
		for (auto& entityVec : m_entityMap | std::views::values)
		{
			removeEntities(entityVec);
		}
		m_toAdd.clear();
	}

	void EntityManager::removeEntities(EntityVec& vec)
	{
		std::erase_if(vec, [](auto const& entity) { return !entity->isActive(); });
	}

	std::shared_ptr<Entity> EntityManager::addEntity(std::string const& tag)
	{
		auto entity = std::make_shared<Entity>(m_totalEntities++, tag);
		m_toAdd.push_back(entity);
		return entity;
	}

	EntityVec const& EntityManager::getEntities() const
	{
		return m_entities;
	}

	EntityVec const& EntityManager::getEntities(std::string const& tag) const
	{
		return m_entityMap.at(tag);
	}

	std::unordered_map<std::string, EntityVec> const& EntityManager::getEntityMap() const
	{
		return m_entityMap;
	}
}