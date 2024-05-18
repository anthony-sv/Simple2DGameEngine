#pragma once
/*
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include "Entity.hpp"
#include "EntityManager.hpp"

/*struct [[nodiscard]] WindowConfig final
{
	int WINDOW_WIDTH,
		WINDOW_HEIGHT,
		FRAME_LIMIT,
		FULLSCREEN_MODE;
};
struct [[nodiscard]] FontConfig final
{
	std::string CONFIGFILE_PATH;
	unsigned int FONT_SIZE,
		FONTCOLOR_RED,
		FONTCOLOR_GREEN,
		FONTCOLOR_BLUE;
};
struct [[nodiscard]] PlayerConfig final
{
	int VERTICES;
	unsigned int FILLCOLOR_RED,
		FILLCOLOR_GREEN,
		FILLCOLOR_BLUE,
		OUTLINECOLOR_RED,
		OUTLINECOLOR_GREEN,
		OUTLINECOLOR_BLUE;
	float SPEED,
		SHAPE_RADIUS,
		COLLISION_RADIUS,
		OUTLINE_THICKNESS;
	bool RENDER;
};

class [[nodiscard]] Game final
{
public:
	explicit [[nodiscard]] Game(std::string const& config);
	~Game();
	void run();
	void setPaused(bool const paused);
	[[nodiscard]] bool isPaused() const;
	[[nodiscard]] bool isRunning() const;
	[[nodiscard]] PlayerConfig const& getPlayerConfig() const;
	[[nodiscard]] FontConfig const& getFontConfig() const;
	[[nodiscard]] WindowConfig const& getWindowConfig() const;
	char imdisplayString[255] = "Sample Text";
	float imcolor[3] = { 0.0f, 1.0f, 1.0f };
private:
	void init(std::string const& path);
	void spawnPlayer();
	void sMovement() const;
	void sUserInput();
	void sGUI();
	void sRender();
	void sCollision();
	sf::RenderWindow m_window;
	sf::Font m_font;
	sf::Text m_text;
	sf::Clock m_deltaClock;
	SGE2D::Entts::EntityManager m_entities;
	std::shared_ptr<SGE2D::Entts::Entity> m_player;
	bool m_paused{ false };
	bool m_running{ true };
	int m_currentFrame{ 0 };
	WindowConfig m_windowConfig;
	FontConfig m_fontConfig;
	PlayerConfig m_playerConfig;
	void parseConfigFile(std::string const& path);
}; */