#include "Scene.hpp"

SGE2D::Scenes::Scene::Scene(GameEngine* gameEngine)
	: m_game{ gameEngine }
{
}

void SGE2D::Scenes::Scene::simulate(std::size_t const& timesUpdate)
{
	// TODO
}

void SGE2D::Scenes::Scene::doAction(Actions const& action)
{
	sDoAction(action);
}

void SGE2D::Scenes::Scene::registerAction(int inputKey, std::string const& actionName)
{
	m_actions[inputKey] = actionName;
}

std::size_t SGE2D::Scenes::Scene::getCurrentFrame() const
{
	return m_currentFrame;
}

std::size_t SGE2D::Scenes::Scene::width() const
{
	return m_game->getWindow().getSize().x;
}

std::size_t SGE2D::Scenes::Scene::height() const
{
	return m_game->getWindow().getSize().y;
}

void SGE2D::Scenes::Scene::setPaused(bool const paused)
{
	m_paused = paused;
}

std::unordered_map<int, std::string> const& SGE2D::Scenes::Scene::getActionMap() const
{
	return m_actions;
}

void SGE2D::Scenes::Scene::drawLine(SGE2D::Math::Vector2D const& point1, SGE2D::Math::Vector2D const& point2) const
{
	sf::Vertex const line[] =
	{
		sf::Vertex(sf::Vector2f(point1.x, point1.y)),
		sf::Vertex(sf::Vector2f(point2.x, point2.y))
	};
	m_game->getWindow().draw(line, 2, sf::Lines);
}
