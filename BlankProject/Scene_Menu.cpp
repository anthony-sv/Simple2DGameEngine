#include "Scene_Menu.hpp"
#include <print>
#include "Scene_Play.hpp"

Scene_Menu::Scene_Menu(GameEngine* gameEngine)
	: Scene{ gameEngine }
{
	init();
}

void Scene_Menu::update()
{
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
	m_game->getWindow().draw(m_menuText);
	for (auto i = 0; i < m_menuStrings.size(); i++)
	{
		if (i == m_menuIndex)
			m_menuItems[i].setFillColor(sf::Color::Black);
		else
			m_menuItems[i].setFillColor(sf::Color::White);
		//m_menuItems[i].setPosition(m_game->getWindow().getSize().x / 2.0f - 26 * (m_menuStrings[i].length() + 1) / 2.0f, m_menuText.getGlobalBounds().top + 10.f + 30.0f * (i + 1));
		m_menuItems[i].setOrigin(round(m_menuItems[i].getGlobalBounds().getSize() / 2.f + m_menuItems[i].getLocalBounds().getPosition()));
		m_menuItems[i].setPosition(m_game->getWindow().getSize().x / 2u, m_menuText.getGlobalBounds().top + 30.0f + 30.0f * (i + 1));
		m_game->getWindow().draw(m_menuItems[i]);
	}
	sf::Text help{ "W:UP	S:DOWN	D:PLAY	ESC:QUIT", m_game->getAssets().getFont("Tech"), 26 };
	help.setFillColor(sf::Color::Black);
	help.setOrigin(round(help.getGlobalBounds().getSize() / 2.f + help.getLocalBounds().getPosition()));
	help.setPosition(m_game->getWindow().getSize().x / 2u, m_game->getWindow().getSize().y - 30.0f * 2.0f);
	m_game->getWindow().draw(help);
}

void Scene_Menu::init()
{
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::D, "PLAY");
	registerAction(sf::Keyboard::Escape, "QUIT");

	m_menuTitle = "MENU";
	auto titleSize{ 30 };

	m_menuText.setString(m_menuTitle);
	m_menuText.setFont(m_game->getAssets().getFont("Tech"));
	m_menuText.setCharacterSize(titleSize);
	m_menuText.setFillColor(sf::Color::Black);
	m_menuText.setPosition(m_game->getWindow().getSize().x / 2.0f - titleSize * (m_menuTitle.length() + 1) / 2.0f, titleSize * 3);

	m_menuStrings.emplace_back("Level 1");
	m_menuStrings.emplace_back("Level 2");
	m_menuStrings.emplace_back("Level 3");

	for (auto i = 0; i < m_menuStrings.size(); i++)
	{
		sf::Text text{ m_menuStrings[i], m_game->getAssets().getFont("Tech"), 26 };
		if (i != m_menuIndex)
			text.setFillColor(sf::Color::Black);
		text.setPosition(m_game->getWindow().getSize().x / 2.0f - 26 * (m_menuStrings[i].length() + 1) / 2.0f, m_menuText.getGlobalBounds().top + 10.0f + 30.0f * (i + 1));
		m_menuItems.emplace_back(text);
	}

	m_levelPaths.emplace_back("level1.txt");
	m_levelPaths.emplace_back("level2.txt");
	m_levelPaths.emplace_back("level3.txt");

	m_menuText.setFont(m_game->getAssets().getFont("Tech"));
	m_menuText.setCharacterSize(64);
}

void Scene_Menu::onEnd()
{
	m_game->quit();
}

sf::Vector2f Scene_Menu::round(const sf::Vector2f vector)
{
	return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}
