#include "EntityManager.hpp"

#include <ranges>
#include <print>

namespace SGE2D::Entts
{
	EntityManager::EntityManager() = default;

	void EntityManager::update()
	{
		// Add new entities to the vector of all entities and the entity map
		for (auto const& entity : m_toAdd)
		{
			m_entities.push_back(entity);
			m_entityMap[entity->getTag()].push_back(entity);
		}

		// Remove non-active entities from the vector of all entities
		removeEntities(m_entities);

		// Remove non-active entities from the entity map
		for (auto& entityVec : m_entityMap | std::views::values)
			//for (auto& [key, value] : m_entityMap)  //C++20: way of iterating through [key, value] pairs in a map
		{
			removeEntities(entityVec);
		}

		// Clear the list of entities to add
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