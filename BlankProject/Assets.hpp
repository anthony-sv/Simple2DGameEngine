#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.hpp"

namespace SGE2D // now once per game but can be once per scene
{
	class Assets
	{
	public:
		void addTexture(std::string const& name, std::string const& path);
		void addSound(std::string const& name, std::string const& path);
		void addFont(std::string const& name, std::string const& path);
		void addAnimation(std::string const& name, Animation::Animation const& animation);

		sf::Texture const& getTexture(std::string const& name) const;
		sf::Sound const& getSound(std::string const& name) const;
		sf::Font const& getFont(std::string const& name) const;
		Animation::Animation const& getAnimation(std::string const& name) const;
		void loadFromFile(std::string const& path);
	private:
		std::unordered_map<std::string, sf::Texture> m_textures;
		std::unordered_map<std::string, sf::Sound> m_sounds;
		std::unordered_map<std::string, sf::Font> m_fonts;
		std::unordered_map<std::string, Animation::Animation> m_animations;
	};
}
