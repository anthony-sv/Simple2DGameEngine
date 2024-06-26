#include <print>
#include "MotorVideojuegos.hpp"
#include "Accion.hpp"
#include "SMenu.hpp"

void
MotorVideojuegos::correr()
{
	while (estaCorriendo())
	{
		actualizar();
	}
}

void
MotorVideojuegos::actualizar()
{
	sEntradaUsuario();
	if (obtenerEscenaActual())
	{
		obtenerEscenaActual()->actualizar();
	}
	m_ventana.display();
}

void
MotorVideojuegos::salir()
{
	m_corriendo = false;
}

void
MotorVideojuegos::cambiarEscena(
	std::string const& nombre,
	std::shared_ptr<MVS2D::Escenas::Escena> escena,
	bool terminarEscenaActual)
{
	if (escena)
	{
		m_escenas[nombre] = escena;
		m_escenaActual = nombre;
	}
	if (!m_escenas.contains(nombre))
	{
		m_escenaActual = "N/A";
	}
}

MVS2D::Activos::ManejadorActivos const&
MotorVideojuegos::obtenerActivos() const
{
	return m_activos;
}

sf::RenderWindow&
MotorVideojuegos::obtenerVentana()
{
	return m_ventana;
}

void
MotorVideojuegos::sEntradaUsuario()
{
	sf::Event evento;
	while (m_ventana.pollEvent(evento))
	{
		if (evento.type == sf::Event::Closed)
		{
			salir();
		}
		if (evento.type == sf::Event::Resized)
		{
			sf::FloatRect areaVisible(0, 0, evento.size.width, evento.size.height);
			m_ventana.setView(sf::View(areaVisible));
		}
		if (evento.type == sf::Event::KeyPressed)
		{
			if (evento.key.code == sf::Keyboard::X)
			{
				std::println("Guardando captura de pantalla...");
				sf::Texture textura;
				textura.create(m_ventana.getSize().x, m_ventana.getSize().y);
				textura.update(m_ventana);
				if (textura.copyToImage().saveToFile("screenshot.png"))
				{
					std::println("Captura de pantalla guardada en screenshot.png");
				}
			}
		}
		if (evento.type == sf::Event::KeyPressed || evento.type == sf::Event::KeyReleased)
		{
			if (!obtenerEscenaActual()->obtenerMapaAcciones().contains(evento.key.code))
			{
				continue;
			}
			std::string const tipoAccion{ (evento.type == sf::Event::KeyPressed) ? "INICIO" : "FIN" };
			obtenerEscenaActual()->realizarAccion({ obtenerEscenaActual()->obtenerMapaAcciones().at(evento.key.code), tipoAccion });
		}
	}
}

bool
MotorVideojuegos::estaCorriendo() const
{
	return m_corriendo && m_ventana.isOpen();
}

MotorVideojuegos::MotorVideojuegos(
	std::string const& ruta)
{
	alInicializar(ruta);
}

void
MotorVideojuegos::alInicializar(
	std::string const& ruta)
{
	m_activos.cargarDesdeArchivo(ruta);
	m_ventana.create(sf::VideoMode(1280, 768), "Sandbox TT");
	m_ventana.setVerticalSyncEnabled(true);
	m_ventana.setFramerateLimit(60);
	cambiarEscena("MENU", std::make_shared<SMenu>(this));
}

std::shared_ptr<MVS2D::Escenas::Escena>
MotorVideojuegos::obtenerEscenaActual()
{
	return m_escenas.at(m_escenaActual);
}