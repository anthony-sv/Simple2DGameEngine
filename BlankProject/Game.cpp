#include "Game.hpp"

#include <print>
#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>

Game::Game(std::string const& config)
{
	init(config);
}

Game::~Game()
{
	ImGui::SFML::Shutdown();
}

void Game::parseConfigFile(std::string const& path)
{
	std::ifstream ifs(path);
	std::string line;
	while (std::getline(ifs, line))
	{
		std::istringstream iss(line);
		std::string first;
		if (iss >> first)
		{
			if (first == "Window")
			{
				iss >> m_windowConfig.WINDOW_WIDTH >>
					m_windowConfig.WINDOW_HEIGHT >>
					m_windowConfig.FRAME_LIMIT >>
					m_windowConfig.FULLSCREEN_MODE;
			}
			else if (first == "Font")
			{
				iss >> m_fontConfig.CONFIGFILE_PATH >>
					m_fontConfig.FONT_SIZE >>
					m_fontConfig.FONTCOLOR_RED >>
					m_fontConfig.FONTCOLOR_GREEN >>
					m_fontConfig.FONTCOLOR_BLUE;
			}
			else if (first == "Player")
			{
				iss >> m_playerConfig.SHAPE_RADIUS >>
					m_playerConfig.COLLISION_RADIUS >>
					m_playerConfig.SPEED >>
					m_playerConfig.FILLCOLOR_RED >>
					m_playerConfig.FILLCOLOR_GREEN >>
					m_playerConfig.FILLCOLOR_BLUE >>
					m_playerConfig.OUTLINECOLOR_RED >>
					m_playerConfig.OUTLINECOLOR_GREEN >>
					m_playerConfig.OUTLINECOLOR_BLUE >>
					m_playerConfig.OUTLINE_THICKNESS >>
					m_playerConfig.VERTICES >>
					m_playerConfig.RENDER;
			}
		}
	}
}

void Game::init(std::string const& path)
{
	parseConfigFile(path);
	imcolor[0] = static_cast<float>(m_playerConfig.FILLCOLOR_RED) / 255.0f;
	imcolor[1] = static_cast<float>(m_playerConfig.FILLCOLOR_GREEN) / 255.0f;
	imcolor[2] = static_cast<float>(m_playerConfig.FILLCOLOR_BLUE) / 255.0f;
	if (!m_font.loadFromFile(m_fontConfig.CONFIGFILE_PATH))
	{
		// Print an error message to the console if the font failed to load
		std::println(std::cerr, "Error loading font");
		std::quick_exit(EXIT_FAILURE);
	}
	auto const windowWidth = m_windowConfig.WINDOW_WIDTH;
	auto const windowHeight = m_windowConfig.WINDOW_HEIGHT;
	// Create a window of size windowWidth x windowHeight
	m_window.create(sf::VideoMode(windowWidth, windowHeight), "SGE2D");
	// Limit the framerate to 60 frames per second
	m_window.setFramerateLimit(m_windowConfig.FRAME_LIMIT);
	// For reference: top-left corner is (0, 0) and bottom-right corner is (windowWidth, windowHeight)

	// Initialize ImGui
	ImGui::SFML::Init(m_window);

	m_text = { "Sample Text", m_font, m_fontConfig.FONT_SIZE };
	m_text.setPosition(0, static_cast<float>(m_window.getSize().y - m_text.getCharacterSize()));

	/*
	* Game init logic
	*/
	spawnPlayer(); // Spawn the player at the start of the game
}

void Game::run()
{
	while (m_running)
	{
		// update the entity manager
		m_entities.update();

		// required update call to imgui
		ImGui::SFML::Update(m_window, m_deltaClock.restart());

		sMovement();
		sCollision();
		sUserInput();
		sGUI();
		sRender();

		// Increment the current frame
		m_currentFrame++;
	}
}

void Game::spawnPlayer()
{
	// We create every entity by calling EntityManager::addEntity(tag)
	auto const entity = m_entities.addEntity("player");

	// Create a circle shape
	entity->cCircleShape = std::make_unique<SGE2D::Components::CCircleShape>(
		m_playerConfig.SHAPE_RADIUS,
		m_playerConfig.VERTICES,
		sf::Color{ static_cast<unsigned char>(m_playerConfig.FILLCOLOR_RED), static_cast<unsigned char>(m_playerConfig.FILLCOLOR_GREEN), static_cast<unsigned char>(m_playerConfig.FILLCOLOR_BLUE) },
		sf::Color{ static_cast<unsigned char>(m_playerConfig.OUTLINECOLOR_RED), static_cast<unsigned char>(m_playerConfig.OUTLINECOLOR_GREEN), static_cast<unsigned char>(m_playerConfig.OUTLINECOLOR_BLUE) },
		m_playerConfig.OUTLINE_THICKNESS);

	// Add a transform component to the player so that we know how to move it
	entity->cTransform = std::make_unique<SGE2D::Components::CTransform>(
		// vector2D at center of screen
		SGE2D::Math::Vector2D{ static_cast<float>(m_window.getSize().x) / 2.0f, static_cast<float>(m_window.getSize().y) / 2.0f },
		SGE2D::Math::Vector2D{ m_playerConfig.SPEED, m_playerConfig.SPEED },
		SGE2D::Math::Vector2D{ 1.0f, 1.0f },
		0.0f);

	// Add an input component to the player so that we can use inputs to move it
	entity->cInput = std::make_unique<SGE2D::Components::CInput>();

	// Add a collision component to the player so that we can check for collisions
	entity->cCollision = std::make_unique<SGE2D::Components::CCollision>(m_playerConfig.COLLISION_RADIUS);

	// Add a render component to the player so that we can draw it
	entity->cRender = std::make_unique<SGE2D::Components::CRender>(m_playerConfig.RENDER);

	// Since we want this Entity to be our player, set our Game's m_player variable to be this Entity
	m_player = entity; // Breaking the encapsulation of the EntityManager but it's fine for now
}

PlayerConfig const& Game::getPlayerConfig() const
{
	return m_playerConfig;
}

WindowConfig const& Game::getWindowConfig() const
{
	return m_windowConfig;
}

FontConfig const& Game::getFontConfig() const
{
	return m_fontConfig;
}

void Game::sMovement() const
{
	for (auto& entity : m_entities.getEntities())
	{
		if (entity->getTag() == "player")
		{
			SGE2D::Math::Vector2D playerVelocity{};
			if (entity->cInput->up)
			{
				playerVelocity.y -= 1.0f;
			}
			if (entity->cInput->down)
			{
				// speed from config
				playerVelocity.y += 1.0f;
			}
			if (entity->cInput->left)
			{
				playerVelocity.x -= 1.0f;
			}
			if (entity->cInput->right)
			{
				playerVelocity.x += 1.0f;
			}

			if (playerVelocity.x != 0.0f && playerVelocity.y != 0.0f)
			{
				playerVelocity = playerVelocity.normalize();
			}
			m_player->cTransform->velocity = playerVelocity;
			m_player->cTransform->position += m_player->cTransform->velocity;
		}
	}
	m_player->cTransform->position.x += m_player->cTransform->velocity.x;
	m_player->cTransform->position.y += m_player->cTransform->velocity.y;
}

void Game::sCollision()
{
	for (auto& entity : m_entities.getEntities())
	{
		if (entity->getTag() == "player")
		{
			// Check if the entity is out of bounds
			if (// Calculate the bounds based on the collision radius on if-init
				auto const collisionRadius = entity->cCollision->radius,
				leftBound = collisionRadius,
				rightBound = static_cast<float>(m_window.getSize().x) - collisionRadius,
				bottomBound = static_cast<float>(m_window.getSize().y) - collisionRadius,
				topBound = collisionRadius;
				entity->cTransform->position.x < leftBound ||
				entity->cTransform->position.x > rightBound ||
				entity->cTransform->position.y < topBound ||
				entity->cTransform->position.y > bottomBound)
			{
				// If out of bounds, destroy the entity and respawn it after a delay
				entity->destroy();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				spawnPlayer();
			}
		}
	}
}

void Game::sGUI()
{
	ImGui::Begin("ImGUI Window");
	ImGui::Text("Hello, world!");
	ImGui::Checkbox("Draw Circle", &m_player->cRender->render);

	// Get the current radius of the circle shape
	float radius = m_player->cCircleShape->circleShape.getRadius();
	ImGui::SliderFloat("Circle Radius", &radius, 0.0f, 300.0f);
	// Adjust the position of the shape to maintain its center
	auto const currentPosition = m_player->cTransform->position;
	float const currentRadius = m_player->cCircleShape->circleShape.getRadius();
	m_player->cTransform->position.x = currentPosition.x + (currentRadius - radius) / 2.0f;
	m_player->cTransform->position.y = currentPosition.y + (currentRadius - radius) / 2.0f;
	// Update the circle shape's radius
	m_player->cCircleShape->circleShape.setRadius(radius);

	auto vertices = static_cast<int>(m_player->cCircleShape->circleShape.getPointCount());
	ImGui::SliderInt("Sides", &vertices, 3, 64);
	m_player->cCircleShape->circleShape.setPointCount(vertices);

	ImGui::ColorEdit3("Color Circle", imcolor);
	m_player->cCircleShape->circleShape.setFillColor(sf::Color{ static_cast<unsigned char>(imcolor[0] * 255), static_cast<unsigned char>(imcolor[1] * 255), static_cast<unsigned char>(imcolor[2] * 255) });

	ImGui::InputText("Text", imdisplayString, 255);
	if (ImGui::Button("Set Text"))
	{
		m_text.setString(imdisplayString);
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset Circle"))
	{
		m_player->cTransform->position.x = m_player->cCircleShape->circleShape.getRadius();
		m_player->cTransform->position.y = m_player->cCircleShape->circleShape.getRadius();
	}
	ImGui::End();
}

void Game::sRender()
{
	m_window.clear();

	for (auto& entity : m_entities.getEntities())
	{
		if (entity->cRender->render)
		{
			// Set the position of the shape based on the entity's transform->position
			entity->cCircleShape->circleShape.setPosition(entity->cTransform->position.x, entity->cTransform->position.y);
			// Set the origin of the shape to be the center of the shape
			entity->cCircleShape->circleShape.setOrigin(entity->cCircleShape->circleShape.getRadius(), entity->cCircleShape->circleShape.getRadius());
			// Set the rotation of the shape based on the entity's transform->angle
			entity->cTransform->angle += 1.0f;
			entity->cCircleShape->circleShape.setRotation(entity->cTransform->angle);
			// Draw the entity's sf::CircleShape
			m_window.draw(entity->cCircleShape->circleShape);
		}
	}

	// Draw the text
	m_window.draw(m_text);

	// Draw the ui last
	ImGui::SFML::Render(m_window);
	m_window.display();
}

void Game::sUserInput()
{
	// Event handling
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		// Pass the event to ImGui to be parsed
		ImGui::SFML::ProcessEvent(m_window, event);

		// Event handling for closing the window
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		// Event handling for key presses
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = true;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = true;
				break;
			default: break;
			}
		}

		// Event handling for key releases
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = false;
				break;
			default: break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			// This line ignores mouse events if ImGui is the thing clicked
			if (ImGui::GetIO().WantCaptureMouse) { continue; }

			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::println("Left Mouse Button Clicked at ({}, {})", event.mouseButton.x, event.mouseButton.y);
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::println("Right Mouse Button Clicked at ({}, {})", event.mouseButton.x, event.mouseButton.y);
			}
		}
	}
}