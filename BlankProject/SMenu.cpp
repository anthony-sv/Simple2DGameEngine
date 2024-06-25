#include "SMenu.hpp"
#include <print>
#include "SJugar.hpp"

SMenu::SMenu(MotorVideojuegos* motorVideojuegos)
	: Escena{ motorVideojuegos }
{
	alInicializar();
}

void SMenu::actualizar()
{
	sRenderizar();
}

void SMenu::sRealizarAccion(MVS2D::Accion const& action)
{
	if (action.getType() == "START")
	{
		if (action.getName() == "UP")
		{
			if (m_indexMenu > 0)
			{
				m_indexMenu--;
			}
			else
			{
				m_indexMenu = m_cadenasDelMenu.size() - 1;
			}
		}
		else if (action.getName() == "DOWN")
		{
			m_indexMenu = (m_indexMenu + 1) % m_cadenasDelMenu.size();
		}
		else if (action.getName() == "PLAY")
		{
			std::println("PLAY");
			m_juego->cambiarEscena("PLAY", std::make_shared<SJugar>(m_juego, m_rutasNiveles[m_indexMenu]));
		}
		else if (action.getName() == "QUIT")
		{
			alFinalizar();
		}
	}
}

void SMenu::sRenderizar()
{
	m_juego->obtenerVentana().clear(sf::Color(100, 100, 255));
	m_juego->obtenerVentana().draw(m_textoMenu);
	for (auto i = 0; i < m_cadenasDelMenu.size(); i++)
	{
		if (i == m_indexMenu)
			m_itemsMenu[i].setFillColor(sf::Color::Black);
		else
			m_itemsMenu[i].setFillColor(sf::Color::White);
		m_itemsMenu[i].setOrigin(redondear(m_itemsMenu[i].getGlobalBounds().getSize() / 2.f + m_itemsMenu[i].getLocalBounds().getPosition()));
		m_itemsMenu[i].setPosition(m_juego->obtenerVentana().getSize().x / 2u,
			m_textoMenu.getGlobalBounds().top + 30.0f + 30.0f * (i + 1));
		m_juego->obtenerVentana().draw(m_itemsMenu[i]);
	}
	sf::Text help{ "W:UP	S:DOWN	D:PLAY	ESC:QUIT", m_juego->obtenerActivos().obtenerFuente("Tech"), 26 };
	help.setFillColor(sf::Color::Black);
	help.setOrigin(redondear(help.getGlobalBounds().getSize() / 2.0f + help.getLocalBounds().getPosition()));
	help.setPosition(m_juego->obtenerVentana().getSize().x / 2u, m_juego->obtenerVentana().getSize().y - 30.0f * 2.0f);
	m_juego->obtenerVentana().draw(help);
}

void SMenu::alInicializar()
{
	registrarAccion(sf::Keyboard::W, "UP");
	registrarAccion(sf::Keyboard::S, "DOWN");
	registrarAccion(sf::Keyboard::D, "PLAY");
	registrarAccion(sf::Keyboard::Escape, "QUIT");

	m_tituloMenu = "MENU";
	constexpr auto titleSize{ 30 };

	m_textoMenu.setString(m_tituloMenu);
	m_textoMenu.setFont(m_juego->obtenerActivos().obtenerFuente("Tech"));
	m_textoMenu.setCharacterSize(titleSize);
	m_textoMenu.setFillColor(sf::Color::Black);
	m_textoMenu.setPosition(m_juego->obtenerVentana().getSize().x / 2.0f - titleSize * (m_tituloMenu.length() + 1) / 2.0f, titleSize * 2);

	m_cadenasDelMenu.emplace_back("Level 1");
	m_cadenasDelMenu.emplace_back("Level 2");

	for (auto i = 0; i < m_cadenasDelMenu.size(); i++)
	{
		sf::Text text{ m_cadenasDelMenu[i], m_juego->obtenerActivos().obtenerFuente("Tech"), 26 };
		if (i != m_indexMenu)
			text.setFillColor(sf::Color::Black);
		text.setPosition(m_juego->obtenerVentana().getSize().x / 2.0f - 26 * (m_cadenasDelMenu[i].length() + 1) / 2.0f, m_textoMenu.getGlobalBounds().top + 10.0f + 30.0f * (i + 1));
		m_itemsMenu.emplace_back(text);
	}

	m_rutasNiveles.emplace_back("nivel1.txt");
	m_rutasNiveles.emplace_back("nivel2.txt");

	m_textoMenu.setFont(m_juego->obtenerActivos().obtenerFuente("Tech"));
	m_textoMenu.setCharacterSize(64);
}

void SMenu::alFinalizar()
{
	m_juego->salir();
}

sf::Vector2f SMenu::redondear(sf::Vector2f const vector)
{
	return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}