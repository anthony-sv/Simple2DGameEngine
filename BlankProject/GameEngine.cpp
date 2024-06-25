#include <print>
#include "GameEngine.hpp"
#include "Actions.hpp"
#include "Scene_Menu.hpp"

void GameEngine::run()
{
	while (isRunning())
	{
		update();
	}
}

void GameEngine::update()
{
	sUserInput();
	if (currentScene())
	{
		currentScene()->update();
	}
	m_window.display();
}

void GameEngine::quit()
{
	m_running = false;
}

void GameEngine::changeScene(std::string const& name, std::shared_ptr<SGE2D::Scenes::Scene> scene, bool endCurrentScene)
{
	if (scene)
	{
		m_scenes[name] = scene;
		m_currentScene = name;
	}
	if (!m_scenes.contains(name))
	{
		m_currentScene = "NONE";
	}
}

SGE2D::Assets const& GameEngine::getAssets() const
{
	return m_assets;
}

sf::RenderWindow& GameEngine::getWindow()
{
	return m_window;
}

void GameEngine::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			quit();
		}
		// catch the resize events
		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			m_window.setView(sf::View(visibleArea));
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::X)
			{
				std::println("Saving screenshot...");
				sf::Texture texture;
				texture.create(m_window.getSize().x, m_window.getSize().y);
				texture.update(m_window);
				if (texture.copyToImage().saveToFile("test.png"))
				{
					std::println("Screenshot saved to test.png");
				}
			}
		}
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			if (!currentScene()->getActionMap().contains(event.key.code))
			{
				continue;
			}
			std::println("Key pressed: {}", static_cast<int>(event.key.code));
			std::string const actionType{ (event.type == sf::Event::KeyPressed) ? "START" : "END" };
			currentScene()->doAction({ currentScene()->getActionMap().at(event.key.code), actionType });
		}
	}
}

bool GameEngine::isRunning() const
{
	return m_running && m_window.isOpen();
}

GameEngine::GameEngine(std::string const& path)
{
	init(path);
}

void GameEngine::init(std::string const& path)
{
	m_assets.loadFromFile(path);
	m_window.create(sf::VideoMode(1280, 768), "Game Test 1");
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60);
	changeScene("MENU", std::make_shared<Scene_Menu>(this));
}

std::shared_ptr<SGE2D::Scenes::Scene> GameEngine::currentScene()
{
	return m_scenes.at(m_currentScene);
}
