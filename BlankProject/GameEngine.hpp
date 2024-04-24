#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Assets.hpp"

class GameEngine
{
public:
	void run();
	void update();
	void quit();
	void changeScene(std::unique_ptr<SGE2D::Scene> scene);
	SGE2D::Assets& getAssets();
	sf::RenderWindow& getWindow();
	void sUserInput();
private:
	std::unordered_map<std::string, SGE2D::Scene> m_scenes;
	sf::RenderWindow m_window;
	SGE2D::Assets m_assets;
	std::string m_currentScene;
	bool m_running{ false };
	void init();
	std::unique_ptr<SGE2D::Scene> currentScene();
};

