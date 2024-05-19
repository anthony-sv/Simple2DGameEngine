#include "Scene_Menu.hpp"
#include <print>
#include "Scene_Play.hpp"

Scene_Menu::Scene_Menu(GameEngine* gameEngine)
	: Scene(gameEngine)
{
	init();
}

void Scene_Menu::update()
{
	m_entities.update();
	sRender();
}

void Scene_Menu::sDoAction(SGE2D::Actions const& action)
{
	if (action.getType() == "START")
	{
		if (action.getName() == "UP")
		{
			if (m_menuIndex > 0)
			{
				m_menuIndex--;
			}
			else
			{
				m_menuIndex = m_menuStrings.size() - 1;
			}
		}
		else if (action.getName() == "DOWN")
		{
			m_menuIndex = (m_menuIndex + 1) % m_menuStrings.size();
		}
		else if (action.getName() == "PLAY")
		{
			std::println("PLAY");
			m_game->changeScene("PLAY", std::make_shared<Scene_Play>(m_game, m_levelPaths[m_menuIndex]));
		}
		else if (action.getName() == "QUIT")
		{
			onEnd();
		}
	}
}

void Scene_Menu::sRender()
{
	m_game->getWindow().clear(sf::Color(100, 100, 255));
	for (auto menu : m_menuStrings)
	{
		// display menu text in screen
	}
}

void Scene_Menu::init()
{
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::D, "PLAY");
	registerAction(sf::Keyboard::Escape, "QUIT");

	m_menuTitle = "MENU";
	m_menuStrings.emplace_back("Level 1");
	m_menuStrings.emplace_back("Level 2");
	m_menuStrings.emplace_back("Level 3");

	m_levelPaths.emplace_back("Level1.txt");
	m_levelPaths.emplace_back("Level2.txt");
	m_levelPaths.emplace_back("Level3.txt");

	m_menuText.setFont(m_game->getAssets().getFont("Tech"));
	m_menuText.setCharacterSize(64);
}

void Scene_Menu::onEnd()
{
	m_game->quit();
}
