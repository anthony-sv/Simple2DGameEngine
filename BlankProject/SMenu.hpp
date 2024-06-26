#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Escena.hpp"
#include "MotorVideojuegos.hpp"

class SMenu : public MVS2D::Escenas::Escena
{
public:
	explicit [[nodiscard]] SMenu(MotorVideojuegos* motorVideojuegos = nullptr);
	void sRenderizar() override;
protected:
	static sf::Vector2f redondear(sf::Vector2f const vector);
	std::string m_tituloMenu;
	std::vector <std::string> m_cadenasDelMenu;
	sf::Text m_textoMenu;
	std::vector <std::string> m_rutasNiveles;
	std::vector <sf::Text> m_itemsMenu;
	std::size_t m_indiceMenu{ 0 };
	void alInicializar();
	void actualizar() override;
	void alFinalizar() override;
	void sRealizarAccion(MVS2D::Accion const& action) override;
};