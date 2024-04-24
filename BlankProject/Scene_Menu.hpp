#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Scene.hpp"

class Scene_Menu : public SGE2D::Scene
{
public:
	void update() override;
private:
	std::vector <std::string> m_menuStrings;
	sf::Text m_menuText;
	std::vector <std::string> m_levelPaths;
	int m_menuIndex;

	void init() override;
	// Systems
	void sRender() override;
	void sDoAction(SGE2D::Actions action) override;
};

