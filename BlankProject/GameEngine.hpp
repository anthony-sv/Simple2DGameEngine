#pragma once
#include <string>
#include <print>
#include <unordered_map>
#include <SFML/Graphics.hpp>
//#include "Scene.hpp"
#include "Assets.hpp"

namespace SGE2D::Scenes
{
	class Scene;
}

class GameEngine final
{
public:
	void run();
	void update();
	void quit();
	void changeScene(std::string const& name, std::shared_ptr<SGE2D::Scenes::Scene> scene, bool endCurrentScene = false);
	SGE2D::Assets const& getAssets() const;
	sf::RenderWindow& getWindow();
	void sUserInput();
	bool isRunning() const;
	explicit [[nodiscard]] GameEngine(std::string const& path);

private:
	std::unordered_map < std::string, std::shared_ptr<SGE2D::Scenes::Scene>> m_scenes;
	sf::RenderWindow m_window;
	SGE2D::Assets m_assets;
	std::string m_currentScene;
	bool m_running{ true };
	std::size_t m_simulationSpeed{ 1 };
	void init(std::string const& path);
	std::shared_ptr<SGE2D::Scenes::Scene> currentScene();
};