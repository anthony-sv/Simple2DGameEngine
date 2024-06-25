#include <print>
#include "MotorVideojuegos.hpp"
#include "Accion.hpp"
#include "SMenu.hpp"

void MotorVideojuegos::correr()
{
	while (estaCorriendo())
	{
		actualizar();
	}
}

void MotorVideojuegos::actualizar()
{
	sEntradaUsuario();
	if (obtenerEscenaActual())
	{
		obtenerEscenaActual()->actualizar();
	}
	m_ventana.display();
}

void MotorVideojuegos::salir()
{
	m_corriendo = false;
}

void MotorVideojuegos::cambiarEscena(std::string const& nombre, std::shared_ptr<MVS2D::Escenas::Escena> escena, bool terminarEscenaActual)
{
	if (escena)
	{
		m_escenas[nombre] = escena;
		m_escenaActual = nombre;
	}
	if (!m_escenas.contains(nombre))
	{
		m_escenaActual = "NONE";
	}
}

MVS2D::Activos::ManejadorActivos const& MotorVideojuegos::obtenerActivos() const
{
	return m_activos;
}

sf::RenderWindow& MotorVideojuegos::obtenerVentana()
{
	return m_ventana;
}

void MotorVideojuegos::sEntradaUsuario()
{
	sf::Event event;
	while (m_ventana.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			salir();
		}
		// catch the resize events
		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			m_ventana.setView(sf::View(visibleArea));
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::X)
			{
				std::println("Saving screenshot...");
				sf::Texture texture;
				texture.create(m_ventana.getSize().x, m_ventana.getSize().y);
				texture.update(m_ventana);
				if (texture.copyToImage().saveToFile("test.png"))
				{
					std::println("Screenshot saved to test.png");
				}
			}
		}
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			if (!obtenerEscenaActual()->obtenerMapaAcciones().contains(event.key.code))
			{
				continue;
			}
			std::println("Key pressed: {}", static_cast<int>(event.key.code));
			std::string const actionType{ (event.type == sf::Event::KeyPressed) ? "START" : "END" };
			obtenerEscenaActual()->realizarAccion({ obtenerEscenaActual()->obtenerMapaAcciones().at(event.key.code), actionType });
		}
	}
}

bool MotorVideojuegos::estaCorriendo() const
{
	return m_corriendo && m_ventana.isOpen();
}

MotorVideojuegos::MotorVideojuegos(std::string const& ruta)
{
	alInicializar(ruta);
}

void MotorVideojuegos::alInicializar(std::string const& ruta)
{
	m_activos.cargarDesdeArchivo(ruta);
	m_ventana.create(sf::VideoMode(1280, 768), "Game Test 1");
	m_ventana.setVerticalSyncEnabled(true);
	m_ventana.setFramerateLimit(60);
	cambiarEscena("MENU", std::make_shared<SMenu>(this));
}

std::shared_ptr<MVS2D::Escenas::Escena> MotorVideojuegos::obtenerEscenaActual()
{
	return m_escenas.at(m_escenaActual);
}
