#include "SMenu.hpp"
#include <print>
#include "SJugar.hpp"

SMenu::SMenu(
	MotorVideojuegos* motorVideojuegos)
	: Escena{ motorVideojuegos }
{
	alInicializar();
}

void
SMenu::actualizar()
{
	sRenderizar();
}

void
SMenu::sRealizarAccion(
	MVS2D::Accion const& action)
{
	if (action.obtenerTipo() == "INICIO")
	{
		if (action.obtenerNombre() == "ARRIBA")
		{
			if (m_indiceMenu > 0)
			{
				m_indiceMenu--;
			}
			else
			{
				m_indiceMenu = m_cadenasDelMenu.size() - 1;
			}
		}
		else if (action.obtenerNombre() == "ABAJO")
		{
			m_indiceMenu = (m_indiceMenu + 1) % m_cadenasDelMenu.size();
		}
		else if (action.obtenerNombre() == "JUGAR")
		{
			m_juego->cambiarEscena("JUGAR", std::make_shared<SJugar>(m_juego, m_rutasNiveles[m_indiceMenu]));
		}
		else if (action.obtenerNombre() == "SALIR")
		{
			alFinalizar();
		}
	}
}

void
SMenu::sRenderizar()
{
	m_juego->obtenerVentana().clear(sf::Color(100, 100, 255));
	m_juego->obtenerVentana().draw(m_textoMenu);
	for (auto i = 0; i < m_cadenasDelMenu.size(); i++)
	{
		if (i == m_indiceMenu)
			m_itemsMenu[i].setFillColor(sf::Color::White);
		else
			m_itemsMenu[i].setFillColor(sf::Color::Black);
		m_itemsMenu[i].setOrigin(redondear(m_itemsMenu[i].getGlobalBounds().getSize() / 2.f + m_itemsMenu[i].getLocalBounds().getPosition()));
		m_itemsMenu[i].setPosition(
			m_juego->obtenerVentana().getSize().x / 2u,
			m_textoMenu.getGlobalBounds().top + 30.0f + 30.0f * (i + 1));
		m_juego->obtenerVentana().draw(m_itemsMenu[i]);
	}
	sf::Text textoAyuda{ "W:ARRIBA	S:ABAJO	D:JUGAR	ESC:SALIR", m_juego->obtenerActivos().obtenerFuente("Tech"), 26 };
	textoAyuda.setFillColor(sf::Color::Black);
	textoAyuda.setOrigin(redondear(textoAyuda.getGlobalBounds().getSize() / 2.0f + textoAyuda.getLocalBounds().getPosition()));
	textoAyuda.setPosition(m_juego->obtenerVentana().getSize().x / 2u, m_juego->obtenerVentana().getSize().y - 30.0f * 2.0f);
	m_juego->obtenerVentana().draw(textoAyuda);
}

void
SMenu::alInicializar()
{
	registrarAccion(sf::Keyboard::W, "ARRIBA");
	registrarAccion(sf::Keyboard::S, "ABAJO");
	registrarAccion(sf::Keyboard::D, "JUGAR");
	registrarAccion(sf::Keyboard::Escape, "SALIR");

	m_tituloMenu = "MENU";
	constexpr auto tamanioTitulo{ 30 };

	m_textoMenu.setString(m_tituloMenu);
	m_textoMenu.setFont(m_juego->obtenerActivos().obtenerFuente("Tech"));
	m_textoMenu.setCharacterSize(tamanioTitulo);
	m_textoMenu.setFillColor(sf::Color::Black);
	m_textoMenu.setPosition(m_juego->obtenerVentana().getSize().x / 2.0f - tamanioTitulo * (m_tituloMenu.length() + 1) / 2.0f, tamanioTitulo * 2);

	m_cadenasDelMenu.emplace_back("Nivel 1");
	m_cadenasDelMenu.emplace_back("Nivel 2");

	for (auto i = 0; i < m_cadenasDelMenu.size(); i++)
	{
		sf::Text textoNiveles{ m_cadenasDelMenu[i], m_juego->obtenerActivos().obtenerFuente("Tech"), 26 };
		if (i != m_indiceMenu)
			textoNiveles.setFillColor(sf::Color::Black);
		textoNiveles.setPosition(
			m_juego->obtenerVentana().getSize().x / 2.0f - 26 * (m_cadenasDelMenu[i].length() + 1) / 2.0f,
			m_textoMenu.getGlobalBounds().top + 10.0f + 30.0f * (i + 1));
		m_itemsMenu.emplace_back(textoNiveles);
	}

	m_rutasNiveles.emplace_back("nivel1.txt");
	m_rutasNiveles.emplace_back("nivel2.txt");

	m_textoMenu.setFont(m_juego->obtenerActivos().obtenerFuente("Tech"));
	m_textoMenu.setCharacterSize(64);
}

void
SMenu::alFinalizar()
{
	m_juego->salir();
}

sf::Vector2f
SMenu::redondear(
	sf::Vector2f const vector)
{
	return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}