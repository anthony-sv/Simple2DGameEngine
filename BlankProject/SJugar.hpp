#pragma once
#include "Escena.hpp"



class SJugar : public MVS2D::Escenas::Escena
{
	struct [[nodiscard]] ConfiguracionJugador final
	{
		float COORDENADA_X, COORDENADA_Y, TAMANIO_AABB_ANCHO, TAMANIO_AABB_ALTO, VELOCIDAD, VELOCIDAD_MAXIMA, VELOCIDAD_SALTO, GRAVEDAD;
	};
public:
	[[nodiscard]] explicit SJugar(MotorVideojuegos* motorVideojuegos, std::string const& rutaNivelInicial);
	void actualizar() override;
	// Systems
	void sRenderizar() override;
	void sAnimacion() const;
	void sMovimiento() const;
	void sColision() const;
	void sRealizarAccion(MVS2D::Accion const& accion) override;
	void alFinalizar() override;
	void cargarNivel(std::string const& ruta);
	MVS2D::Matematicas::Vector2D conversionCoordenadasAPixel(float x, float y, std::shared_ptr<MVS2D::Entidades::Entidad> const& entidad) const;
	void aparecerJugador();
protected:
	std::shared_ptr<MVS2D::Entidades::Entidad> m_jugador;
	std::string m_rutaNivelInicial;
	ConfiguracionJugador m_configuracionJugador;
	MVS2D::Matematicas::Vector2D const tamanioMatriz{ 64,64 };

	void alInicializar(std::string const& levelPath);
};