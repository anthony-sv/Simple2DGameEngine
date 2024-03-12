#include <iostream>
#include <print>

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include <boost/log/trivial.hpp>

#include "Vector2D.hpp"

int main(int argc, char** argv)
{
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	SGE2D::Math::Vector2D vec1{ 2, 4 };
	vec1 = vec1 * 2;
	std::cout << "vec1:" << vec1 << '\n';
	std::println("{}", vec1);
	constexpr auto windowWidth = 1280;
	constexpr auto windowHeight = 720;
	// Create a window of size 1280x720 
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Window");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);
	// For reference: top-left corner is (0, 0) and bottom-right corner is (windowWidth, windowHeight)

	// Initialize ImGui
	ImGui::SFML::Init(window);
	// Create a clock to measure time, for the ImGui window
	sf::Clock deltaClock;

	// Set the global scale of the UI, does not affect the window size nor the font size
	ImGui::GetStyle().ScaleAllSizes(1.0f);

	// The imgui color {r,g,b} wheel requires floats from 0-1 instead of ints from 0-255
	float color[3] = { 0.0f, 1.0f, 1.0f }; // Cyan

	// Shape data
	float circleRadius = 50; // Radius of the circle
	auto circleSegments = 32; // Number of segments in the circle
	auto circleSpeedX = 1.0f;
	auto circleSpeedY = 0.5f;
	auto drawCircle = true; // Whether or not to draw the circle
	auto drawText = true; // Whether or not to draw the text

	// Create a circle shape
	sf::CircleShape circleShape(circleRadius, circleSegments);
	// Set the position of the circle to the top-left corner
	circleShape.setPosition(10.0f, 10.0f);

	sf::Font font;

	// Attempt to load the font from disk
	if (!font.loadFromFile("assets/fonts/tech.ttf"))
	{
		// Print an error message to the console if the font failed to load
		std::println(std::cerr, "Error loading font");
		std::exit(EXIT_FAILURE);
	}

	// Create a text object
	sf::Text text{ "Sample Text", font, 24 };
	// Character size is in pixels, so we need to move the text up by the size of the text
	text.setPosition(0, windowHeight - static_cast<float>(text.getCharacterSize()));

	char displayString[255] = "Sample Text";

	// Main loop
	while (window.isOpen())
	{
		// Event handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Pass the event to ImGui to be parsed
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			// Event handling for keyboard input
			if (event.type == sf::Event::KeyPressed)
			{
				// Print the key code to the console
				std::print("Key pressed: {}\n", static_cast<int>(event.key.code));

				// Example of changing the circle speed when a X is pressed
				if (event.key.code == sf::Keyboard::X)
				{
					circleSpeedX *= -1.0f;
				}
			}
		}

		// Update ImGui for this frame with the time that the last frame took to render
		ImGui::SFML::Update(window, deltaClock.restart());

		// ImGui window
		ImGui::Begin("ImGUI Window");
		ImGui::Text("Hello, world!");
		ImGui::Checkbox("Draw Circle", &drawCircle);
		ImGui::SameLine();
		ImGui::Checkbox("Draw Text", &drawText);
		ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
		ImGui::SliderInt("Sides", &circleSegments, 3, 64);
		ImGui::ColorEdit3("Color Circle", color);
		ImGui::InputText("Text", displayString, 255);
		if (ImGui::Button("Set Text"))
		{
			text.setString(displayString);
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset Circle"))
		{
			circleShape.setPosition(0.0f, 0.0f);
		}
		ImGui::End();


		circleShape.setFillColor(sf::Color(
			static_cast<sf::Uint8>(color[0] * 255),
			static_cast<sf::Uint8>(color[1] * 255),
			static_cast<sf::Uint8>(color[2] * 255))
		);
		circleShape.setRadius(circleRadius);
		circleShape.setPointCount(circleSegments);

		// Basic animation - move the circle each frame if it's still in the frame
		circleShape.setPosition(circleShape.getPosition().x + circleSpeedX, circleShape.getPosition().y + circleSpeedY);

		window.clear(); // Clear the window
		if (drawCircle) // Draw the circle if needed
		{
			window.draw(circleShape);
		}
		if (drawText) // Draw the text if needed
		{
			window.draw(text);
		}
		ImGui::SFML::Render(window); // Render the ImGui window on top of the rest
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}