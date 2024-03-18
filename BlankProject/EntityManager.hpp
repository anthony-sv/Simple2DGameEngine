#pragma once
#include "Entity.hpp"
#include <vector>
#include <unordered_map>

namespace SGE2D::Entts
{
	using EntityVec = std::vector<std::shared_ptr<Entity>>;
	using EntityMap = std::unordered_map<std::string, EntityVec>;

	class [[nodiscard]] EntityManager final
	{
	public:
		[[nodiscard]] EntityManager();
		void update();
		std::shared_ptr<Entity> addEntity(std::string const& tag);
		[[nodiscard]] EntityVec const& getEntities() const;
		[[nodiscard]] EntityVec const& getEntities(std::string const& tag) const;
		[[nodiscard]] EntityMap const& getEntityMap() const;
	private:
		static void removeEntities(EntityVec& vec);
		EntityVec m_entities{};
		EntityMap m_entityMap{};
		EntityVec m_toAdd{};
		std::size_t m_totalEntities{ 0 };
	};
};



