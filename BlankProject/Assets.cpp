#include "Assets.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <print>

void SGE2D::Assets::addTexture(std::string const& name, std::string const& path)
{
	sf::Texture texture;
	texture.loadFromFile(path);
	m_textures[name] = texture;
}

void SGE2D::Assets::addSound(std::string const& name, std::string const& path)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void SGE2D::Assets::addFont(std::string const& name, std::string const& path)
{
	m_fonts[name] = sf::Font();
	if (!m_fonts[name].loadFromFile(path))
	{
		std::println(std::cerr, "Could not load Font from {}", path);
	}
}

void SGE2D::Assets::addAnimation(std::string const& name, Animation::Animation const& animation)
{
	m_animations[name] = animation;
}

sf::Texture const& SGE2D::Assets::getTexture(std::string const& name) const
{
	return m_textures.at(name);
}

sf::Sound const& SGE2D::Assets::getSound(std::string const& name) const
{
	return m_sounds.at(name);
}

sf::Font const& SGE2D::Assets::getFont(std::string const& name) const
{
	return m_fonts.at(name);

}

SGE2D::Animation::Animation const& SGE2D::Assets::getAnimation(std::string const& name) const
{
	return m_animations.at(name);
}

void SGE2D::Assets::loadFromFile(std::string const& path)
{
	std::ifstream file(path);
	if (!file) {
		std::println(std::cerr, "Could not load {} file!", path);
		std::quick_exit(-1);
	}

	std::string assetType;
	while (file >> assetType)
	{
		std::string name;
		std::string assetPath;
		if (assetType == "Texture")
		{
			file >> name >> assetPath;
			addTexture(name, assetPath);
		}
		else if (assetType == "Animation")
		{
			int frames, speed;
			file >> name >> assetPath >> frames >> speed;
			sf::Texture const& tex = getTexture(assetPath);
			addAnimation(name, Animation::Animation{ name, tex, static_cast<std::size_t>(frames), static_cast<std::size_t>(speed) });
		}
		else if (assetType == "Font")
		{
			file >> name >> assetPath;
			addFont(name, assetPath);
		}
		else
		{
			std::println(std::cerr, "Incorrect asset type: {}", assetType);
			std::quick_exit(-1);
		}
	}
}