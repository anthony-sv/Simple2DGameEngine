#include "Scene_Play.hpp"

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

	// TODO: Register all other gameplay Actions

	m_gridText.setCharacterSize(12);
	m_gridText.setFont(m_game->getAssets().getFont("Tech"));

	loadLevel(levelPath);
}


SGE2D::Math::Vector2D Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<SGE2D::Entts::Entity> entity)
{
	// TODO: This function takes in a grid (x,y) position and an Entity
	//       Return a Vec2 indicating where the CENTER position of the Entity should be
	// 		 You must use the Entity's Animation size to position it correctly
	//       The size of the grid width and height is stored in gridSize
	//       The bottom-left corner of the Animation should align with the bottom-left of the grid cell
	return { 0,0 };
}

void Scene_Play::loadLevel(std::string const& path)
{
	// reset the entity manager every time we load a new level
	m_entities = SGE2D::Entts::EntityManager{};

	// TODO: read in the level file and add the appropriate entities
	//		 use the PlayerConfig2 struct m_playerConfig to store player properties
	//		 this struct is defined at the top of Scene_Play.hpp

	// NOTE: all of the code below is a samplecode which shows you how to
	//		 set up entities with the new syntax, it should be removed
	spawnPlayer();

	// some sample entities
	auto brick{ m_entities.addEntity("tile") };
	// IMPORTANT: always add the CAnimation component first so that gridToMidPixel works
	brick->cAnimation = std::make_unique<SGE2D::Components::CAnimation>(m_game->getAssets().getAnimation("brick"), true);
	//brick->addComponent<SGE2D::Components::CAnimation>("brick", m_game->getAssets().getAnimation("brick"));
	brick->cTransform = std::make_unique<SGE2D::Components::CTransform>(SGE2D::Math::Vector2D{ 96, 480 });
	// NOTE: You final code should position the entity with the grid x,y position read from
	// brick->addComponent<SGE2D::Components::CTransform>(gridToMidPixel(gridX, gridY, brick));

	if (brick->cAnimation->animation.getName() == "Brick")
	{
		std::println("This could be a good way of identifying if a tile is a brick!");
	}

	auto block{ m_entities.addEntity("tile") };
	block->cAnimation = std::make_unique<SGE2D::Components::CAnimation>(m_game->getAssets().getAnimation("Block"), true);
	//block->addComponent<SGE2D::Components::CAnimation>(m_game->getAssets().getAnimation("Block"), true);
	block->cTransform = std::make_unique<SGE2D::Components::CTransform>(SGE2D::Math::Vector2D{ 224,480 });
	// add a bounding box, this will now show up if we press the 'C' key
	block->cBoundingBox = std::make_unique<SGE2D::Components::CBoundingBoxCollision>(m_game->getAssets().getAnimation("Block").getSize());

	auto question{ m_entities.addEntity("tile") };
	question->cAnimation = std::make_unique<SGE2D::Components::CAnimation>(m_game->getAssets().getAnimation("Question"), true);
	//question->addComponent<SGE2D::Components::CAnimation>(m_game->getAssets().getAnimation("Question"), true);
	question->cTransform = std::make_unique<SGE2D::Components::CTransform>(SGE2D::Math::Vector2D{ 352,480 });

	// NOTE: THIS IS INCREDIBLY IMPORTANT PLEASE READ THIS EXAMPLE
	// Components are now returned by reference, rather than by pointer
	// If you do not specify a reference variable type, it will COPY the component
	// Here is an example:
	//
	// This will COPY the transform into the variable 'transform1' - it is INCORRECT
	// Any changes you make to transform1 will NOT be reflected in the entity
	// auto transform1 = enmtity->get<CTransform>()
	//
	// This will REFERENCE the transform into the variable 'transform2' - it is CORRECT
	// Now any changes you make to transform2 will be reflected in the entity
	// auto& transform2 = entity->get<CTransform>()
}

void Scene_Play::spawnPlayer()
{
	// here is a sample player entity which you can use to construct other entities
	m_player = m_entities.addEntity("Player");
	m_player->cAnimation = std::make_unique<SGE2D::Components::CAnimation>(m_game->getAssets().getAnimation("Stand"), true);
	m_player->cTransform = std::make_unique<SGE2D::Components::CTransform>(SGE2D::Math::Vector2D{ 224, 352 });
	m_player->cBoundingBox = std::make_unique<SGE2D::Components::CBoundingBoxCollision>(SGE2D::Math::Vector2D{ 48, 48 });

	// TODO: be sure to add the remaining components to the player entity
}

void Scene_Play::spawnBullet()
{
	// TODO: this should spawn a bullet at the given entity, going in the direction the entity is facing
}

void Scene_Play::drawLine(SGE2D::Math::Vector2D const& point1, SGE2D::Math::Vector2D const& point2) const
{
	sf::Vertex const line[] =
	{
		sf::Vertex(sf::Vector2f(point1.x, point1.y)),
		sf::Vertex(sf::Vector2f(point2.x, point2.y))
	};
	m_game->getWindow().draw(line, 2, sf::Lines);
}

void Scene_Play::update()
{
	m_entities.update();
	// TODO: implement pause functionality

	sMovement();
	sLifeSpan();
	sCollision();
	sAnimation();
	sRender();
}

void Scene_Play::sMovement()
{
	// TODO: Implement player movement / jumping based on it's CInput component
	// TODO: Implement gravity's effect on the player
	// TODO: Implement the maximum player speed in both X and Y direction (check max)
	// NOTE: Setting an entity's scale.x to -1/1 will make it face left/right
}

void Scene_Play::sLifeSpan()
{
	// TODO: Check lifespan of entities that have them, and destroy them if they go over
}

void Scene_Play::sCollision()
{
	// REMEMBER: SFML's (0,0) position is on the TOP-LEFT corner
	// This means jumping will have a negative Y component
	// and gravity will have a positive Y component
	// Also, something BELOW something else will have a y value GREATER than the other
	// Also, something ABOVE something else will have a y value LESS than the other


	// TODO: Implement Physics::GetOverlap function, use it inside this function

	// TODO: Implement bullet / tile collisions
	// Destroy the tile if has a Brick animation
	// TODO: Implement player / tile collisions and resolutions
	// Update the CState component of the player to score wheter
	// it is currently on the ground or in the air. This will be
	// used by the Animation system
	// TODO: Check to see if the player has fallen down a hole(y > height())
	// TODO: Don't let the player walk off the left side of the map
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
			// check this.
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
		else if (action.getName() == "UP")
		{
			if (m_player && m_player->cInput)
				m_player->cInput->up = true;
		}
	}
	else if (action.getType() == "END")
	{
	}
}


void Scene_Play::sAnimation()
{
	// TODO: Complete the Animation class code first

	// TODO: set the animation of the player based on it's CState component
	// TODO: for each entity with an animation, call entity->getComponent<CAnimation>().animation.update()
	// if the animation is not repeated, and it has ended, destroy the entity
}


void Scene_Play::onEnd()
{
	// TODO: When the scene ends, change back to the menu scene
	// use m_game->changeScene(correct_params);
}


void Scene_Play::sRender()
{
	// color the background darker so you know that the game is paused
	if (!m_paused)
		m_game->getWindow().clear(sf::Color(100, 100, 255));
	else
		m_game->getWindow().clear(sf::Color(50, 50, 150));

	// set the viewport of the window to be centered on the player if it's far enough to the right
	auto& playerPosition = m_player->cTransform->position;
	float windowCenterX = std::max(m_game->getWindow().getSize().x / 2.0f, playerPosition.x);
	sf::View view = m_game->getWindow().getView();
	view.setCenter(windowCenterX, m_game->getWindow().getSize().y - view.getCenter().y);
	m_game->getWindow().setView(view);

	// draw all Entity textures / animations
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

	// draw the grid so that students can easily debug
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
