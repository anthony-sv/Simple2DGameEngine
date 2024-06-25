#include "SJugar.hpp"

#include <iostream>
#include <fstream>
#include <print>

#include "CajaDelimitadora.hpp"
#include "SMenu.hpp"

SJugar::SJugar(MotorVideojuegos* motorVideojuegos, std::string const& rutaNivelInicial)
	: Escena{ motorVideojuegos }, m_rutaNivelInicial{ rutaNivelInicial }
{
	alInicializar(rutaNivelInicial);
}

void SJugar::alInicializar(std::string const& levelPath)
{
	registrarAccion(sf::Keyboard::P, "PAUSE");
	registrarAccion(sf::Keyboard::Escape, "QUIT");
	registrarAccion(sf::Keyboard::W, "UP");

	registrarAccion(sf::Keyboard::W, "JUMP");
	registrarAccion(sf::Keyboard::S, "DOWN");
	registrarAccion(sf::Keyboard::A, "LEFT");
	registrarAccion(sf::Keyboard::D, "RIGHT");

	cargarNivel(levelPath);
}


MVS2D::Matematicas::Vector2D SJugar::conversionCoordenadasAPixel(float x, float y, std::shared_ptr<MVS2D::Entidades::Entidad> const& entidad) const
{
	auto const entitySize = entidad->cAnimacion->animacion.obtenerTamanio();
	return { x * tamanioMatriz.x + entitySize.x / 2.0f,obtenerAltoVentana() - y * tamanioMatriz.y - entitySize.y / 2.0f };
}

void SJugar::cargarNivel(std::string const& ruta)
{
	m_entidades = MVS2D::Entidades::ManejadorEntidades{};

	std::ifstream file{ ruta };
	if (!file)
	{
		std::println(std::cerr, "loadLevel failed! at {}", ruta);
		std::quick_exit(-1);
	}
	std::string entityType;
	while (file >> entityType) {
		if (entityType == "Tile")
		{
			std::string animationName;
			float gridX, gridY;
			file >> animationName >> gridX >> gridY;
			auto const tile = m_entidades.agregarEntidad("Tile");
			tile->cAnimacion = std::make_unique<MVS2D::Componentes::CAnimacion>(m_juego->obtenerActivos().obtenerAnimacion(animationName), true);
			tile->cMovimiento = std::make_unique<MVS2D::Componentes::CMovimiento>(conversionCoordenadasAPixel(gridX, gridY, tile));
			tile->cColisionCajaDelimitadora = std::make_unique<MVS2D::Componentes::CColisionCajaDelimitadora>(tamanioMatriz);
		}
		else if (entityType == "Dec")
		{
			std::string animationName;
			float gridX, gridY;
			file >> animationName >> gridX >> gridY;
			auto const dec = m_entidades.agregarEntidad("Dec");
			dec->cAnimacion = std::make_unique<MVS2D::Componentes::CAnimacion>(m_juego->obtenerActivos().obtenerAnimacion(animationName), true);
			dec->cMovimiento = std::make_unique<MVS2D::Componentes::CMovimiento>(conversionCoordenadasAPixel(gridX, gridY, dec));
		}
		else if (entityType == "Player")
		{
			file >> m_configuracionJugador.COORDENADA_X >> m_configuracionJugador.COORDENADA_Y
				>> m_configuracionJugador.TAMANIO_AABB_ANCHO >> m_configuracionJugador.TAMANIO_AABB_ALTO
				>> m_configuracionJugador.VELOCIDAD
				>> m_configuracionJugador.VELOCIDAD_SALTO
				>> m_configuracionJugador.VELOCIDAD_MAXIMA
				>> m_configuracionJugador.GRAVEDAD;
			aparecerJugador();
		}
		else
		{
			std::println(std::cerr, "Unknown entity type {}", entityType);
		}
	}
}

void SJugar::aparecerJugador()
{
	m_jugador = m_entidades.agregarEntidad("Player");
	m_jugador->cAnimacion = std::make_unique<MVS2D::Componentes::CAnimacion>(m_juego->obtenerActivos().obtenerAnimacion("PlayerA"), true);
	m_jugador->cMovimiento = std::make_unique<MVS2D::Componentes::CMovimiento>(conversionCoordenadasAPixel(m_configuracionJugador.COORDENADA_X, m_configuracionJugador.COORDENADA_Y, m_jugador));
	m_jugador->cColisionCajaDelimitadora = std::make_unique<MVS2D::Componentes::CColisionCajaDelimitadora>(MVS2D::Matematicas::Vector2D{ m_configuracionJugador.TAMANIO_AABB_ANCHO, m_configuracionJugador.TAMANIO_AABB_ALTO });
	m_jugador->cEntrada = std::make_unique<MVS2D::Componentes::CEntrada>();
	m_jugador->cGravedad = std::make_unique<MVS2D::Componentes::CGravedad>(m_configuracionJugador.GRAVEDAD);
	m_jugador->cEstado = std::make_unique<MVS2D::Componentes::CEstado>("Standing");
}

void SJugar::actualizar()
{
	m_entidades.actualizar();

	if (!m_pausado)
	{
		sMovimiento();
		sColision();
		m_frameActual++;
	}
	sAnimacion();
	sRenderizar();
}

void SJugar::sMovimiento() const
{
	m_jugador->cMovimiento->velocidad.x = 0;
	if (!m_jugador && !m_jugador->cEntrada)
		return;

	if (m_jugador->cEntrada->arriba)
	{
		if (m_jugador->cEntrada->puedeSaltar)
		{
			m_jugador->cEntrada->puedeSaltar = false;
			m_jugador->cMovimiento->velocidad.y = -m_configuracionJugador.VELOCIDAD_SALTO;
		}
	}

	if (m_jugador->cEntrada->izquierda)
	{
		m_jugador->cMovimiento->velocidad.x = -m_configuracionJugador.VELOCIDAD;
		if (m_jugador->cMovimiento->escala.x > 0)
		{
			m_jugador->cMovimiento->escala.x = -1;
		}
	}
	else if (m_jugador->cEntrada->derecha)
	{
		m_jugador->cMovimiento->velocidad.x = m_configuracionJugador.VELOCIDAD;
		if (m_jugador->cMovimiento->escala.x < 0)
		{
			m_jugador->cMovimiento->escala.x = 1;
		}
	}

	if (std::abs(m_jugador->cMovimiento->velocidad.y) > 0)
	{
		m_jugador->cEstado->estado = "Jumping";
	}
	else if (std::abs(m_jugador->cMovimiento->velocidad.x) > 0)
	{
		m_jugador->cEstado->estado = "Running";
	}
	else
	{
		m_jugador->cEstado->estado = "Idle";
	}

	for (auto const& entity : m_entidades.obtenerEntidades()) {
		if (entity->cGravedad)
		{
			auto& v = entity->cMovimiento->velocidad;
			v.y += entity->cGravedad->gravedad;
			if (v.y > m_configuracionJugador.VELOCIDAD_MAXIMA)
			{
				v.y = m_configuracionJugador.VELOCIDAD_MAXIMA;
			}
			if (v.x > m_configuracionJugador.VELOCIDAD_MAXIMA)
			{
				v.x = m_configuracionJugador.VELOCIDAD_MAXIMA;
			}
		}
		entity->cMovimiento->posicionAnterior = entity->cMovimiento->posicion;
		entity->cMovimiento->posicion += entity->cMovimiento->velocidad;
	}
}

void SJugar::sColision() const
{
	m_jugador->cGravedad->gravedad = m_configuracionJugador.GRAVEDAD;
	for (auto const& tile : m_entidades.obtenerEntidades("Tile")) {
		auto const overlap = MVS2D::Fisica::CajaDelimitadora::calcularSuperposicion(m_jugador, tile);
		auto const pOverlap = MVS2D::Fisica::CajaDelimitadora::calcularSuperposicionAnterior(m_jugador, tile);
		float const dy = tile->cMovimiento->posicion.y - m_jugador->cMovimiento->posicion.y;
		if (0 < overlap.x && -tamanioMatriz.y < overlap.y && dy > 0)
		{
			if (0 <= overlap.y && pOverlap.y <= 0)
			{
				m_jugador->cEntrada->puedeSaltar = true;
				m_jugador->cGravedad->gravedad = 0;
				m_jugador->cMovimiento->velocidad.y = 0;
				m_jugador->cMovimiento->posicion.y -= overlap.y;
			}
		}
		if (0 < overlap.x && -tamanioMatriz.y < overlap.y && dy < 0)
		{
			if (0 <= overlap.y && pOverlap.y <= 0)
			{
				m_jugador->cMovimiento->posicion.y += overlap.y;
				m_jugador->cMovimiento->velocidad.y = 0;
				if (tile->cAnimacion->animacion.obtenerNombre() == "Brick") {
					std::println("Hit brick from below!");
				}
			}
		}
		float const dx = tile->cMovimiento->posicion.x - m_jugador->cMovimiento->posicion.x;
		if (0 < overlap.y && -tamanioMatriz.x < overlap.x)
		{
			if (0 <= overlap.x && pOverlap.x <= 0)
			{
				if (dx > 0)
				{
					m_jugador->cMovimiento->posicion.x -= overlap.x;
				}
				else {
					m_jugador->cMovimiento->posicion.x += overlap.x;
				}
			}
		}
	}
	if (m_jugador->cMovimiento->posicion.y > obtenerAltoVentana())
	{
		m_jugador->cMovimiento->posicion = conversionCoordenadasAPixel(m_configuracionJugador.COORDENADA_X, m_configuracionJugador.COORDENADA_Y, m_jugador);
	}
	if (m_jugador->cMovimiento->posicion.x < m_jugador->cColisionCajaDelimitadora->tamanio.x / 2.0f)
	{
		m_jugador->cMovimiento->posicion.x = m_jugador->cColisionCajaDelimitadora->tamanio.x / 2.0f;
	}
}

void SJugar::sRealizarAccion(MVS2D::Accion const& accion)
{
	if (accion.getType() == "START")
	{
		if (accion.getName() == "PAUSE")
		{
			ponerPausa(!m_pausado);
		}
		else if (accion.getName() == "QUIT")
		{
			alFinalizar();
		}
		else if (accion.getName() == "JUMP")
		{
			if (m_jugador->cEntrada->puedeSaltar)
			{
				m_jugador->cEntrada->arriba = true;
			}
		}
		else if (accion.getName() == "DOWN")
		{
			m_jugador->cEntrada->abajo = true;
		}
		else if (accion.getName() == "LEFT")
		{
			m_jugador->cEntrada->izquierda = true;
		}
		else if (accion.getName() == "RIGHT")
		{
			m_jugador->cEntrada->derecha = true;
		}
	}
	else if (accion.getType() == "END")
	{
		if (accion.getName() == "JUMP")
		{
			m_jugador->cEntrada->arriba = false;
		}
		else if (accion.getName() == "DOWN")
		{
			m_jugador->cEntrada->abajo = false;
		}
		else if (accion.getName() == "LEFT")
		{
			m_jugador->cEntrada->izquierda = false;
		}
		else if (accion.getName() == "RIGHT")
		{
			m_jugador->cEntrada->derecha = false;
		}
	}
}


void SJugar::sAnimacion() const
{
	if (!m_jugador->cEstado)
		return;
	if (m_jugador->cMovimiento->velocidad.y > 0)
	{
		m_jugador->cEntrada->puedeSaltar = false;
		if (m_jugador->cEstado->estadoAnterior != "Jumping")
		{
			m_jugador->cEstado->estadoAnterior = m_jugador->cEstado->estado;
			m_jugador->cEstado->estado = "Jumping";
			m_jugador->cEstado->cambiarAnimacion = true;
		}
		else
		{
			m_jugador->cEstado->cambiarAnimacion = false;
		}
	}
	else
	{
		if (m_jugador->cMovimiento->velocidad.x != 0)
		{
			if (m_jugador->cEstado->estadoAnterior != "Running")
			{
				m_jugador->cEstado->estadoAnterior = m_jugador->cEstado->estado;
				m_jugador->cEstado->estado = "Running";
				m_jugador->cEstado->cambiarAnimacion = true;
			}
			else
			{
				m_jugador->cEstado->cambiarAnimacion = false;
			}
		}
		else
		{
			if (m_jugador->cEstado->estadoAnterior != "Idle")
			{
				m_jugador->cEstado->estadoAnterior = m_jugador->cEstado->estado;
				m_jugador->cEstado->estado = "Idle";
				m_jugador->cEstado->cambiarAnimacion = true;
			}
			else
			{
				m_jugador->cEstado->cambiarAnimacion = false;
			}
		}
	}
	if (m_jugador->cEstado->cambiarAnimacion)
	{
		std::string animationName;
		if (m_jugador->cEstado->estado == "Idle")
		{
			animationName = "PlayerA";
		}
		else if (m_jugador->cEstado->estado == "Jumping")
		{
			animationName = "Jump";
		}
		else if (m_jugador->cEstado->estado == "Running")
		{
			animationName = "PlayerA";
		}
		m_jugador->cAnimacion = std::make_unique<MVS2D::Componentes::CAnimacion>(m_juego->obtenerActivos().obtenerAnimacion(animationName), true);
	}
	for (auto const& entity : m_entidades.obtenerEntidades())
	{
		if (entity->cAnimacion->animacion.finalizo() && !entity->cAnimacion->repetir)
		{
			entity->destruir();
		}
		if (entity->cAnimacion) {
			entity->cAnimacion->animacion.actualizar();
		}
	}
}

void SJugar::alFinalizar()
{
	m_juego->cambiarEscena("MENU", std::make_shared<SMenu>(m_juego));
}

void SJugar::sRenderizar()
{
	if (!m_pausado)
		m_juego->obtenerVentana().clear(sf::Color(100, 100, 255));
	else
		m_juego->obtenerVentana().clear(sf::Color(0, 255, 0));

	auto& playerPosition = m_jugador->cMovimiento->posicion;
	float windowCenterX = std::max(m_juego->obtenerVentana().getSize().x / 2.0f, playerPosition.x);
	sf::View view = m_juego->obtenerVentana().getView();
	view.setCenter(windowCenterX, m_juego->obtenerVentana().getSize().y - view.getCenter().y);
	m_juego->obtenerVentana().setView(view);

	for (auto& entity : m_entidades.obtenerEntidades())
	{
		auto& transform = entity->cMovimiento;
		if (entity->cAnimacion)
		{
			auto& animation = entity->cAnimacion->animacion;
			animation.obtenerSprite().setPosition(transform->posicion.x, transform->posicion.y);
			animation.obtenerSprite().setScale(transform->escala.x, transform->escala.y);
			animation.obtenerSprite().setRotation(transform->angulo);
			m_juego->obtenerVentana().draw(animation.obtenerSprite());
		}
	}
}