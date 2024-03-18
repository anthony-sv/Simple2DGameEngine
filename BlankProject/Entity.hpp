#pragma once

#include "Components.hpp"
#include <memory>
#include <string>

namespace SGE2D::Entts
{
	class Entity final
	{
	public:
		Entity(std::size_t const& id, std::string const& tag);
		void destroy();
		[[nodiscard]] std::size_t getId() const;
		[[nodiscard]] bool isActive() const;
		[[nodiscard]] std::string const& getTag() const;
		std::unique_ptr<Components::CTransform> cTransform;
		std::unique_ptr<Components::CCircleShape> cCircleShape;
		std::unique_ptr<Components::CInput> cInput;
		std::unique_ptr<Components::CCollision> cCollision;
		std::unique_ptr<Components::CRender> cRender;
	private:
		bool m_active{ true };
		std::size_t m_id{ 0 };
		std::string m_tag{ "default" };
	};
}
