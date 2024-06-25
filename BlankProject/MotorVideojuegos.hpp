#pragma once
#include <string>
#include <print>
#include <unordered_map>
#include <SFML/Graphics.hpp>
//#include "Escena.hpp"
#include "ManejadorActivos.hpp"

namespace MVS2D::Escenas
{
	class Escena;
}

class MotorVideojuegos final
{
public:
	void correr();
	void actualizar();
	void salir();
	void cambiarEscena(std::string const& nombre, std::shared_ptr<MVS2D::Escenas::Escena> escena, bool terminarEscenaActual = false);
	MVS2D::Activos::ManejadorActivos const& obtenerActivos() const;
	sf::RenderWindow& obtenerVentana();
	void sEntradaUsuario();
	bool estaCorriendo() const;
	explicit [[nodiscard]] MotorVideojuegos(std::string const& ruta);

private:
	std::unordered_map < std::string, std::shared_ptr<MVS2D::Escenas::Escena>> m_escenas;
	sf::RenderWindow m_ventana;
	MVS2D::Activos::ManejadorActivos m_activos;
	std::string m_escenaActual;
	bool m_corriendo{ true };
	void alInicializar(std::string const& ruta);
	std::shared_ptr<MVS2D::Escenas::Escena> obtenerEscenaActual();
};