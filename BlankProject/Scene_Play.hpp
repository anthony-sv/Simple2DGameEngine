#pragma once
#include "Game.hpp" // FIXME: This shouldn't be necessary
#include "Scene.hpp"

struct [[nodiscard]] PlayerConfig2 final
{
	float X, Y, CX, CY, SPEED, MAX_SPEED, JUMP, GRAVITY;
	std::string WEAPON;
};

class Scene_Play : public SGE2D::Scene
{
public:
	[[nodiscard]] Scene_Play() = default;
	explicit Scene_Play(GameEngine* gameEngine, std::string const& levelPath);
	void update() override;
	// Systems
	void sRender() override;
	void sAnimation();
	void sMovement();
	void sLifeSpan();
	//void sEnemySpawner();
	void sCollision();
	void sDoAction(SGE2D::Actions const& action) override;
	void sDebug();
	void onEnd() override;
	void loadLevel(std::string const& path);
	SGE2D::Math::Vector2D gridToMidPixel(float gridX, float gridY, std::shared_ptr<SGE2D::Entts::Entity> entity);
	void spawnPlayer();
	void spawnBullet();
protected:
	std::shared_ptr<SGE2D::Entts::Entity> m_player;
	std::string m_levelPath;
	PlayerConfig2 m_playerConfig;
	bool m_drawTextures{ true };
	bool m_drawCollision{ false };
	bool m_drawGrid{ false };
	SGE2D::Math::Vector2D const gridSize{ 32,32 };
	sf::Text m_gridText;

	void init(std::string const& levelPath);
};

