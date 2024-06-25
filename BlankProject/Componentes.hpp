#pragma once
#include "Vector2D.hpp"
#include <SFML/Graphics.hpp>

#include "AnimacionSprite.hpp"

namespace MVS2D::Componentes
{
	struct [[nodiscard]] CMovimiento final
	{
		MVS2D::Matematicas::Vector2D posicion{ 0.0f, 0.0f };
		MVS2D::Matematicas::Vector2D posicionAnterior{ 0.0f, 0.0f };
		MVS2D::Matematicas::Vector2D escala{ 1.0f, 1.0f };
		MVS2D::Matematicas::Vector2D velocidad{ 0.0f, 0.0f };
		float angulo{ 0.0f };

		[[nodiscard]] CMovimiento() = default;
		explicit [[nodiscard]] CMovimiento(MVS2D::Matematicas::Vector2D const& posicion)
			: posicion{ posicion }
		{}
		[[nodiscard]] CMovimiento(MVS2D::Matematicas::Vector2D const& posicion, MVS2D::Matematicas::Vector2D const& velocidad, MVS2D::Matematicas::Vector2D const& escala, float const angulo)
			: posicion{ posicion }, escala{ escala }, velocidad{ velocidad }, angulo{ angulo }
		{}

	};

	struct [[nodiscard]] CEntrada final
	{
		bool arriba{ false };
		bool abajo{ false };
		bool izquierda{ false };
		bool derecha{ false };
		bool puedeSaltar{ true };
		[[nodiscard]] CEntrada() = default;
	};

	struct [[nodiscard]] CRenderizar final
	{
		bool renderizar{ true };
		explicit [[nodiscard]] CRenderizar(bool const renderizar)
			:renderizar{ renderizar } {}
	};

	struct [[nodiscard]] CEstado final
	{
		[[nodiscard]] CEstado() = default;
		explicit [[nodiscard]] CEstado(std::string const& estado)
			: estado{ estado } {}
		std::string estado{ "NONE" };
		std::string estadoAnterior{ "NONE" };
		bool cambiarAnimacion{ false };
	};

	struct [[nodiscard]] CGravedad final
	{
		float gravedad{ 0.0f };
		CGravedad() = default;
		explicit [[nodiscard]] CGravedad(float const gravedad)
			: gravedad{ gravedad } {}
	};

	struct [[nodiscard]] CAnimacion final
	{
		Sistemas::Animaciones::AnimacionSprite animacion;
		bool repetir{ false };
		[[nodiscard]] CAnimacion(Sistemas::Animaciones::AnimacionSprite const& animacion, bool const repetir)
			: animacion{ animacion }, repetir{ repetir } {}
	};

	struct CColisionCajaDelimitadora final
	{
		Matematicas::Vector2D tamanio;
		Matematicas::Vector2D mitadTamanio;
		[[nodiscard]] CColisionCajaDelimitadora() = default;
		explicit [[nodiscard]] CColisionCajaDelimitadora(Matematicas::Vector2D const& tamanio)
			:tamanio{ tamanio }, mitadTamanio{ tamanio / 2.0f } {}
	};
}