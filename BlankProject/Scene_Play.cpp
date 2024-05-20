#include "Scene_Play.hpp"

#include <iostream>
#include <fstream>
#include <print>

#include "BoundingBox.hpp"
#include "Scene_Menu.hpp"

Scene_Play::Scene_Play(GameEngine* gameEngine, std::string const& levelPath)
	: Scene{ gameEngine }, m_levelPath{ levelPath }
{
	init(levelPath);
}

void Scene_Play::init(std::string const& levelPath)
{
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");
	registerAction(sf::Keyboard::W, "UP");

	registerAction(sf::Keyboard::W, "JUMP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::D, "RIGHT");

	m_gridText.setCharacterSize(12);
	m_gridText.setFont(m_game->getAssets().getFont("Tech"));

	loadLevel(levelPath);
}


SGE2D::Math::Vector2D Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<SGE2D::Entts::Entity> const& entity) const
{
	auto const entitySize = entity->cAnimation->animation.getSize();
	return { gridX * gridSize.x + entitySize.x / 2.0f,height() - gridY * gridSize.y - entitySize.y / 2.0f };
}

void Scene_Play::loadLevel(std::string const& path)
{
	m_entities = SGE2D::Entts::EntityManager{};

	std::ifstream file{ path };
	if (!file)
	{
		std::println(std::cerr, "loadLevel failed! at {}", path);
		std::quick_exit(-1);
	}
	std::string entityType;
	while (file >> entityType) {
		if (entityType == "Tile")
		{
			std::string animationName;
			float gridX, gridY;
			file >> animationName >> gridX >> gridY;
			auto const tile = m_entities.addEntity("Tile");
			tile->cAnimation = std::make_unique<SGE2D::Components::CAnimation>(m_game->getAssets().getAnimation(animationName), true);
			tile->cTransform = std::make_unique<SGE2D::Components::CTransform>(gridToMidPixel(gridX, gridY, tile));
			tile->cBoundingBox = std::make_unique<SGE2D::Components::CBoundingBoxCollision>(gridSize);
		}
		else if (entityType == "Dec")
		{
			std::string animationName;
			float gridX, gridY;
			file >> animationName >> gridX >> gridY;
			auto const dec = m_entities.addEntity("Dec");
			dec->cAnimation = std::make_unique<SGE2D::Components::CAnimation>(m_game->getAssets().getAnimation(animationName), true);
			dec->cTransform = std::make_unique<SGE2D::Components::CTransform>(gridToMidPixel(gridX, gridY, dec));
		}
		else if (entityType == "Player")
		{
			file >> m_playerConfig.X >> m_playerConfig.Y
				>> m_playerConfig.CX >> m_playerConfig.CY
				>> m_playerConfig.SPEED
				>> m_playerConfig.JUMP
				>> m_playerConfig.MAX_SPEED
				>> m_playerConfig.GRAVITY;
			spawnPlayer();
		}
		else
		{
			std::println(std::cerr, "Unknown entity type {}", entityType);
		}
	}
}

void Scene_Play::spawnPlayer()
{
	m_player = m_entities.addEntity("Player");
	m_player->cAnimation = std::make_unique<SGE2D::Components::CAnimation>(m_game->getAssets().getAnimation("Stand"), true);
	m_player->cTransform = std::make_unique<SGE2D::Components::CTransform>(gridToMidPixel(m_playerConfig.X, m_playerConfig.Y, m_player));
	m_player->cBoundingBox = std::make_unique<SGE2D::Components::CBoundingBoxCollision>(SGE2D::Math::Vector2D{ m_playerConfig.CX, m_playerConfig.CY });
	m_player->cInput = std::make_unique<SGE2D::Components::CInput>();
	m_player->cGravity = std::make_unique<SGE2D::Components::CGravity>(m_playerConfig.GRAVITY);
	m_player->cState = std::make_unique<SGE2D::Components::CState>("Standing");
}

void Scene_Play::update()
{
	m_entities.update();

	if (!m_paused)
	{
		sMovement();
		sCollision();
		m_currentFrame++;
	}
	sAnimation();
	sRender();
}

void Scene_Play::sMovement() const
{
	m_player->cTransform->velocity.x = 0;
	if (!m_player && !m_player->cInput)
		return;

	if (m_player->cInput->up)
	{
		if (m_player->cInput->canJump)
		{
			m_player->cInput->canJump = false;
			m_player->cTransform->velocity.y = -m_playerConfig.JUMP;
		}
	}

	if (m_player->cInput->left)
	{
		m_player->cTransform->velocity.x = -m_playerConfig.SPEED;
		if (m_player->cTransform->scale.x > 0)
		{
			m_player->cTransform->scale.x = -1;
		}
	}
	else if (m_player->cInput->right)
	{
		m_player->cTransform->velocity.x = m_playerConfig.SPEED;
		if (m_player->cTransform->scale.x < 0)
		{
			m_player->cTransform->scale.x = 1;
		}
	}

	if (std::abs(m_player->cTransform->velocity.y) > 0)
	{
		m_player->cState->state = "Jumping";
	}
	else if (std::abs(m_player->cTransform->velocity.x) > 0)
	{
		m_player->cState->state = "Running";
	}
	else
	{
		m_player->cState->state = "Idle";
	}

	for (auto const& entity : m_entities.getEntities()) {
		if (entity->cGravity)
		{
			auto& v = entity->cTransform->velocity;
			v.y += entity->cGravity->gravity;
			if (v.y > m_playerConfig.MAX_SPEED)
			{
				v.y = m_playerConfig.MAX_SPEED;
			}
			if (v.x > m_playerConfig.MAX_SPEED)
			{
				v.x = m_playerConfig.MAX_SPEED;
			}
		}
		entity->cTransform->previousPosition = entity->cTransform->position;
		entity->cTransform->position += entity->cTransform->velocity;
	}
}

void Scene_Play::sCollision() const
{
	m_player->cGravity->gravity = m_playerConfig.GRAVITY;
	for (auto const& tile : m_entities.getEntities("Tile")) {
		auto const overlap = SGE2D::Physics::BoundingBox::getOverlap(m_player, tile);
		auto const pOverlap = SGE2D::Physics::BoundingBox::getPreviousOverlap(m_player, tile);
		float const dy = tile->cTransform->position.y - m_player->cTransform->position.y;
		if (0 < overlap.x && -gridSize.y < overlap.y && dy > 0)
		{
			if (0 <= overlap.y && pOverlap.y <= 0)
			{
				m_player->cInput->canJump = true;
				m_player->cGravity->gravity = 0;
				m_player->cTransform->velocity.y = 0;
				m_player->cTransform->position.y -= overlap.y;
			}
		}
		if (0 < overlap.x && -gridSize.y < overlap.y && dy < 0)
		{
			if (0 <= overlap.y && pOverlap.y <= 0)
			{
				m_player->cTransform->position.y += overlap.y;
				m_player->cTransform->velocity.y = 0;
				if (tile->cAnimation->animation.getName() == "Brick") {
					std::println("Hit brick from below!");
				}
			}
		}
		float const dx = tile->cTransform->position.x - m_player->cTransform->position.x;
		if (0 < overlap.y && -gridSize.x < overlap.x)
		{
			if (0 <= overlap.x && pOverlap.x <= 0)
			{
				if (dx > 0)
				{
					m_player->cTransform->position.x -= overlap.x;
				}
				else {
					m_player->cTransform->position.x += overlap.x;
				}
			}
		}
	}
	if (m_player->cTransform->position.y > height())
	{
		m_player->cTransform->position = gridToMidPixel(m_playerConfig.X, m_playerConfig.Y, m_player);
	}
	if (m_player->cTransform->position.x < m_player->cBoundingBox->size.x / 2.0f)
	{
		m_player->cTransform->position.x = m_player->cBoundingBox->size.x / 2.0f;
	}
}

void Scene_Play::sDoAction(SGE2D::Actions const& action)
{
	if (action.getType() == "START")
	{
		if (action.getName() == "PAUSE")
		{
			setPaused(!m_paused);
		}
		else if (action.getName() == "QUIT")
		{
			onEnd();
		}
		else if (action.getName() == "TOGGLE_TEXTURE")
		{
			m_drawTextures = !m_drawTextures;
		}
		else if (action.getName() == "TOGGLE_COLLISION")
		{
			m_drawCollision = !m_drawCollision;
		}
		else if (action.getName() == "TOGGLE_GRID")
		{
			m_drawGrid = !m_drawGrid;
		}
		else if (action.getName() == "JUMP")
		{
			if (m_player->cInput->canJump)
			{
				m_player->cInput->up = true;
			}
		}
		else if (action.getName() == "DOWN")
		{
			m_player->cInput->down = true;
		}
		else if (action.getName() == "LEFT")
		{
			m_player->cInput->left = true;
		}
		else if (action.getName() == "RIGHT")
		{
			m_player->cInput->right = true;
		}
	}
	else if (action.getType() == "END")
	{
		if (action.getName() == "JUMP")
		{
			m_player->cInput->up = false;
		}
		else if (action.getName() == "DOWN")
		{
			m_player->cInput->down = false;
		}
		else if (action.getName() == "LEFT")
		{
			m_player->cInput->left = false;
		}
		else if (action.getName() == "RIGHT")
		{
			m_player->cInput->right = false;
		}
	}
}


void Scene_Play::sAnimation() const
{
	if (!m_player->cState)
		return;
	if (m_player->cTransform->velocity.y > 0)
	{
		m_player->cInput->canJump = false;
		if (m_player->cState->previousState != "Jumping")
		{
			m_player->cState->previousState = m_player->cState->state;
			m_player->cState->state = "Jumping";
			m_player->cState->changeAnimation = true;
		}
		else
		{
			m_player->cState->changeAnimation = false;
		}
	}
	else
	{
		if (m_player->cTransform->velocity.x != 0)
		{
			if (m_player->cState->previousState != "Running")
			{
				m_player->cState->previousState = m_player->cState->state;
				m_player->cState->state = "Running";
				m_player->cState->changeAnimation = true;
			}
			else
			{
				m_player->cState->changeAnimation = false;
			}
		}
		else
		{
			if (m_player->cState->previousState != "Idle")
			{
				m_player->cState->previousState = m_player->cState->state;
				m_player->cState->state = "Idle";
				m_player->cState->changeAnimation = true;
			}
			else
			{
				m_player->cState->changeAnimation = false;
			}
		}
	}
	if (m_player->cState->changeAnimation)
	{
		std::string animationName;
		if (m_player->cState->state == "Idle")
		{
			animationName = "Stand";
		}
		else if (m_player->cState->state == "Jumping")
		{
			animationName = "Jump";
		}
		else if (m_player->cState->state == "Running")
		{
			animationName = "Stand";
		}
		m_player->cAnimation = std::make_unique<SGE2D::Components::CAnimation>(m_game->getAssets().getAnimation(animationName), true);
	}
	for (auto const& entity : m_entities.getEntities())
	{
		if (entity->cAnimation->animation.hasEnded() && !entity->cAnimation->repeat)
		{
			entity->destroy();
		}
		if (entity->cAnimation) {
			entity->cAnimation->animation.update();
		}
	}
}

void Scene_Play::onEnd()
{
	m_game->changeScene("MENU", std::make_shared<Scene_Menu>(m_game));
}

void Scene_Play::sRender()
{
	if (!m_paused)
		m_game->getWindow().clear(sf::Color(100, 100, 255));
	else
		m_game->getWindow().clear(sf::Color(50, 50, 150));

	auto& playerPosition = m_player->cTransform->position;
	float windowCenterX = std::max(m_game->getWindow().getSize().x / 2.0f, playerPosition.x);
	sf::View view = m_game->getWindow().getView();
	view.setCenter(windowCenterX, m_game->getWindow().getSize().y - view.getCenter().y);
	m_game->getWindow().setView(view);

	if (m_drawTextures)
	{
		for (auto& entity : m_entities.getEntities())
		{
			auto& transform = entity->cTransform;
			if (entity->cAnimation)
			{
				auto& animation = entity->cAnimation->animation;
				animation.getSprite().setPosition(transform->position.x, transform->position.y);
				animation.getSprite().setScale(transform->scale.x, transform->scale.y);
				animation.getSprite().setRotation(transform->angle);
				m_game->getWindow().draw(animation.getSprite());
			}
		}
	}

	if (m_drawCollision)
	{
		for (auto& entity : m_entities.getEntities())
		{
			if (entity->cBoundingBox)
			{
				auto& box = entity->cBoundingBox;
				auto& transform = entity->cTransform;
				sf::RectangleShape rect;
				rect.setSize({ box->size.x - 1, box->size.y - 1 });
				rect.setOrigin(box->halfSize.x, box->halfSize.y);
				rect.setPosition(transform->position.x, transform->position.y);
				rect.setFillColor({ 0,0,0,0 });
				rect.setOutlineColor({ 255,255,255,255 });
				rect.setOutlineThickness(1);
				m_game->getWindow().draw(rect);
			}
		}
	}

	if (m_drawGrid)
	{
		float leftX = m_game->getWindow().getView().getCenter().x - width() / 2;
		float rightX = leftX + width() + gridSize.x;
		float nextGridX = leftX - ((int)leftX % (int)gridSize.x);

		for (float x = nextGridX; x < rightX; x += gridSize.x)
		{
			drawLine({ x,0 }, { x, static_cast<float>(height()) });
		}

		for (float y = 0; y < height(); y += gridSize.y)
		{
			drawLine({ leftX, height() - y }, { rightX, height() - y });

			for (float x = nextGridX; x < rightX; x += gridSize.x)
			{
				std::string xCell = std::to_string((int)(x / gridSize.x));
				std::string yCell = std::to_string((int)(y / gridSize.y));
				m_gridText.setString("(" + xCell + "," + yCell + ")");
				m_gridText.setPosition(x + 3, height() - y - gridSize.y + 2);
				m_game->getWindow().draw(m_gridText);
			}
		}
	}
}