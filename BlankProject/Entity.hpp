#pragma once

#include "Components.hpp"
#include <memory>
#include <string>

namespace SGE2D::Entts
{
	class Entity
	{
	public:
		void destroy();
		[[nodiscard]] std::size_t getId() const;
		[[nodiscard]] bool isActive() const;
		[[nodiscard]] std::string const& getTag() const;
	private:
		bool m_active{ true };
		std::size_t m_id{ 0 };
		std::string m_tag{ "default" };
		Entity(std::size_t const& id, std::string const& tag);
		std::unique_ptr<Components::CTransform> m_cTransform;
		std::unique_ptr<Components::CShape> m_cShape;
		std::unique_ptr<Components::CInput> m_cInput;
	};
}
