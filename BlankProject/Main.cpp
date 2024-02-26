#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML Window");
	ImGui::SFML::Init(window);

	sf::CircleShape shape(100.f, 100);
	shape.setFillColor(sf::Color(204, 77, 5));
	shape.setOrigin(100, 100);
	shape.setPosition(300, 300);

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("ImGUI Window");
		ImGui::Text("Hello, world!");
		ImGui::End();

		window.clear(sf::Color(18, 33, 43));
		window.draw(shape);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}