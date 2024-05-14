#include "Scene.hpp"

SGE2D::Scene::Scene(std::shared_ptr<GameEngine> const& gameEngine)
	: m_game(gameEngine)
{
}

void SGE2D::Scene::simulate(int const& timesUpdate)
{
	// TODO
}

void SGE2D::Scene::doAction(Actions const& action)
{
	sDoAction(action);
}

void SGE2D::Scene::registerAction(int inputKey, std::string const& actionName)
{
	m_actions[inputKey] = actionName;
}

int SGE2D::Scene::getCurrentFrame() const
{
	return m_currentFrame;
}

void SGE2D::Scene::setPaused(bool const paused)
{
	m_paused = paused;
}

std::unordered_map<int, std::string> const& SGE2D::Scene::getActionMap() const
{
	return m_actions;
}
