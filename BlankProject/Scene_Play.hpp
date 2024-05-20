#pragma once
#include "Scene.hpp"

struct [[nodiscard]] PlayerConfig final
{
	float X, Y, CX, CY, SPEED, MAX_SPEED, JUMP, GRAVITY;
};

class Scene_Play : public SGE2D::Scenes::Scene
{
public:
	[[nodiscard]] explicit Scene_Play(GameEngine* gameEngine, std::string const& levelPath);
	void update() override;
	// Systems
	void sRender() override;
	void sAnimation() const;
	void sMovement() const;
	void sCollision() const;
	void sDoAction(SGE2D::Actions const& action) override;
	void onEnd() override;
	void loadLevel(std::string const& path);
	SGE2D::Math::Vector2D gridToMidPixel(float gridX, float gridY, std::shared_ptr<SGE2D::Entts::Entity> const& entity) const;
	void spawnPlayer();
protected:
	std::shared_ptr<SGE2D::Entts::Entity> m_player;
	std::string m_levelPath;
	PlayerConfig m_playerConfig;
	bool m_drawTextures{ true };
	bool m_drawCollision{ false };
	bool m_drawGrid{ false };
	SGE2D::Math::Vector2D const gridSize{ 64,64 };
	sf::Text m_gridText;

	void init(std::string const& levelPath);
};