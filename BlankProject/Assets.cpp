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
	std::ifstream ifs(path);
	std::string line;
	while (std::getline(ifs, line))
	{
		std::istringstream iss(line);
		std::string first;
		if (iss >> first)
		{
			std::string name, path;
			if (first == "Font")
			{
				iss >> name >> path;
				sf::Font font;
				if (!font.loadFromFile(path))
				{
					// Print an error message to the console if the font failed to load
					std::println(std::cerr, "Error loading font");
					std::quick_exit(EXIT_FAILURE);
				}
				m_fonts[name] = font;
			}
			else if (first == "Texture")
			{
				iss >> name >> path;
				sf::Texture texture;
				if (!texture.loadFromFile(path))
				{
					// Print an error message to the console if the texture failed to load
					std::println(std::cerr, "Error loading texture");
					std::quick_exit(EXIT_FAILURE);
				}
				m_textures[name] = texture;
			}
			else if (first == "Animation")
			{
				iss >> name >> path; // Name, textName
				if (m_textures.contains(path))
					m_animations[name] = { name, m_textures[path] };
			}
		}
	}
}
