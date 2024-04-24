#pragma once
#include "Actions.hpp"
#include "EntityManager.hpp"
#include "GameEngine.hpp"

namespace SGE2D
{
	class Scene
	{
	public:
		virtual void update() = 0;
		virtual void sDoAction(Actions action) = 0;
		virtual void sRender() = 0;

		virtual ~Scene();

		void simulate(int const& timesUpdate);
		void doAction(Actions action);
		void registerAction(Actions action);
	private:
		virtual void init() = 0;
		GameEngine m_game;
		Entts::EntityManager m_entities;
		int m_currentFrame{ 0 };
		std::unordered_map<int, std::string> m_actionMap;
		bool m_paused{ false };
		bool m_hasEnded{ false };
	};
}

