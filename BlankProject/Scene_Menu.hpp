#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "GameEngine.hpp"

class Scene_Menu : public SGE2D::Scenes::Scene
{
public:
	explicit [[nodiscard]] Scene_Menu(GameEngine* gameEngine = nullptr);
	void sRender() override;
protected:
	static sf::Vector2f round(sf::Vector2f const vector);
	std::string m_menuTitle;
	std::vector <std::string> m_menuStrings;
	sf::Text m_menuText;
	std::vector <std::string> m_levelPaths;
	std::vector <sf::Text> m_menuItems;
	std::size_t m_menuIndex{ 0 };
	void init();
	void update() override;
	void onEnd() override;
	void sDoAction(SGE2D::Actions const& action) override;
};