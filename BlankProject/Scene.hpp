#pragma once
#include "GameEngine.hpp"
#include "Actions.hpp"
#include "EntityManager.hpp"

class GameEngine;
namespace SGE2D::Scenes
{
	class Scene
	{
	public:
		virtual void update() = 0;
		virtual void sDoAction(Actions const& action) = 0;
		virtual void sRender() = 0;

		//[[nodiscard]] Scene() = default;
		[[nodiscard]] explicit Scene(GameEngine* gameEngine);
		//virtual ~Scene();

		void simulate(std::size_t const& frames);
		virtual void doAction(Actions const& action);
		void registerAction(int inputKey, std::string const& name);
		std::unordered_map<int, std::string> const& getActionMap() const;
		std::size_t getCurrentFrame() const;
		bool hasEnded() const;

		std::size_t width() const;
		std::size_t height() const;
	protected:
		GameEngine* m_game;
		Entts::EntityManager m_entities;
		std::size_t m_currentFrame{ 0 };
		std::unordered_map<int, std::string> m_actions;
		bool m_paused{ false };
		bool m_hasEnded{ false };
		virtual void onEnd() = 0;
		void setPaused(bool const paused);
	};
}

