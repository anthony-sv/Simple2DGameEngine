#pragma once
#include "Game.hpp" // FIXME: This shouldn't be necessary
#include "Scene.hpp"

class Scene_Play : public SGE2D::Scene
{
public:
	void update() override;

private:
	std::string m_levelPath;
	std::unique_ptr<SGE2D::Entts::Entity> m_player;
	PlayerConfig m_playerConfig;
	void init() override;
	// Systems
	void sAnimation();
	void sMovement();
	void sEnemySpawner();
	void sCollision();
	void sRender() override;
	void sDoAction(SGE2D::Actions action) override;
	void sDebug();
};

