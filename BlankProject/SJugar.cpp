#include "SJugar.hpp"

#include <iostream>
#include <fstream>
#include <print>

#include "CajaDelimitadora.hpp"
#include "SMenu.hpp"

SJugar::SJugar(
	MotorVideojuegos* motorVideojuegos,
	std::string const& rutaNivelInicial)
	: Escena{ motorVideojuegos },
	m_rutaNivelInicial{ rutaNivelInicial }
{
	alInicializar(rutaNivelInicial);
}

void
SJugar::alInicializar(
	std::string const& levelPath)
{
	registrarAccion(sf::Keyboard::P, "PAUSA");
	registrarAccion(sf::Keyboard::Escape, "SALIR");

	registrarAccion(sf::Keyboard::W, "SALTAR");
	registrarAccion(sf::Keyboard::S, "ABAJO");
	registrarAccion(sf::Keyboard::A, "IZQUIERDA");
	registrarAccion(sf::Keyboard::D, "DERECHA");

	cargarNivel(levelPath);
}


MVS2D::Matematicas::Vector2D
SJugar::conversionCoordenadasAPixel(
	float x,
	float y,
	std::shared_ptr<MVS2D::Entidades::Entidad> const& entidad) const
{
	auto const tamanioEntidad = entidad->cAnimacion->animacion.obtenerTamanio();
	return { x * tamanioMatriz.x + tamanioEntidad.x / 2.0f,obtenerAltoVentana() - y * tamanioMatriz.y - tamanioEntidad.y / 2.0f };
}

void
SJugar::cargarNivel(
	std::string const& ruta)
{
	m_entidades = MVS2D::Entidades::ManejadorEntidades{};

	std::ifstream archivoNivel{ ruta };
	if (!archivoNivel)
	{
		std::println(std::cerr, "Fallo el cargar el arhivo del nivel: {}", ruta);
		std::quick_exit(-1);
	}
	std::string tipoEntidad;
	while (archivoNivel >> tipoEntidad) {
		if (tipoEntidad == "Mosaico")
		{
			std::string nombreAnimacion;
			float coordenadaX, coordenadaY;
			archivoNivel >> nombreAnimacion >> coordenadaX >> coordenadaY;
			auto const mosaico = m_entidades.agregarEntidad("Mosaico");
			mosaico->cAnimacion = std::make_unique<MVS2D::Componentes::CAnimacion>(m_juego->obtenerActivos().obtenerAnimacion(nombreAnimacion), true);
			mosaico->cMovimiento = std::make_unique<MVS2D::Componentes::CMovimiento>(conversionCoordenadasAPixel(coordenadaX, coordenadaY, mosaico));
			mosaico->cColisionCajaDelimitadora = std::make_unique<MVS2D::Componentes::CColisionCajaDelimitadora>(tamanioMatriz);
		}
		else if (tipoEntidad == "Calcomania")
		{
			std::string nombreAnimacion;
			float coordenadaX, coordenadaY;
			archivoNivel >> nombreAnimacion >> coordenadaX >> coordenadaY;
			auto const calcomania = m_entidades.agregarEntidad("Dec");
			calcomania->cAnimacion = std::make_unique<MVS2D::Componentes::CAnimacion>(m_juego->obtenerActivos().obtenerAnimacion(nombreAnimacion), true);
			calcomania->cMovimiento = std::make_unique<MVS2D::Componentes::CMovimiento>(conversionCoordenadasAPixel(coordenadaX, coordenadaY, calcomania));
		}
		else if (tipoEntidad == "Jugador")
		{
			archivoNivel >> m_configuracionJugador.COORDENADA_X >> m_configuracionJugador.COORDENADA_Y
				>> m_configuracionJugador.TAMANIO_AABB_ANCHO >> m_configuracionJugador.TAMANIO_AABB_ALTO
				>> m_configuracionJugador.VELOCIDAD
				>> m_configuracionJugador.VELOCIDAD_SALTO
				>> m_configuracionJugador.VELOCIDAD_MAXIMA
				>> m_configuracionJugador.GRAVEDAD;
			aparecerJugador();
		}
		else
		{
			std::println(std::cerr, "Tipo de Entidad desconocido: {}", tipoEntidad);
		}
	}
}

void
SJugar::aparecerJugador()
{
	m_jugador = m_entidades.agregarEntidad("Jugador");
	m_jugador->cAnimacion = std::make_unique<MVS2D::Componentes::CAnimacion>(m_juego->obtenerActivos().obtenerAnimacion("PlayerA"), true);
	m_jugador->cMovimiento = std::make_unique<MVS2D::Componentes::CMovimiento>(conversionCoordenadasAPixel(m_configuracionJugador.COORDENADA_X, m_configuracionJugador.COORDENADA_Y, m_jugador));
	m_jugador->cColisionCajaDelimitadora = std::make_unique<MVS2D::Componentes::CColisionCajaDelimitadora>(MVS2D::Matematicas::Vector2D{ m_configuracionJugador.TAMANIO_AABB_ANCHO, m_configuracionJugador.TAMANIO_AABB_ALTO });
	m_jugador->cEntrada = std::make_unique<MVS2D::Componentes::CEntrada>();
	m_jugador->cGravedad = std::make_unique<MVS2D::Componentes::CGravedad>(m_configuracionJugador.GRAVEDAD);
	m_jugador->cEstado = std::make_unique<MVS2D::Componentes::CEstado>("Parado");
}

void
SJugar::actualizar()
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

void
SJugar::sMovimiento() const
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
		m_jugador->cEstado->estado = "Saltando";
	}
	else if (std::abs(m_jugador->cMovimiento->velocidad.x) > 0)
	{
		m_jugador->cEstado->estado = "Corriendo";
	}
	else
	{
		m_jugador->cEstado->estado = "Parado";
	}

	for (auto const& entidad : m_entidades.obtenerEntidades()) {
		if (entidad->cGravedad)
		{
			auto& velocidad = entidad->cMovimiento->velocidad;
			velocidad.y += entidad->cGravedad->gravedad;
			if (velocidad.y > m_configuracionJugador.VELOCIDAD_MAXIMA)
			{
				velocidad.y = m_configuracionJugador.VELOCIDAD_MAXIMA;
			}
			if (velocidad.x > m_configuracionJugador.VELOCIDAD_MAXIMA)
			{
				velocidad.x = m_configuracionJugador.VELOCIDAD_MAXIMA;
			}
		}
		entidad->cMovimiento->posicionAnterior = entidad->cMovimiento->posicion;
		entidad->cMovimiento->posicion += entidad->cMovimiento->velocidad;
	}
}

void
SJugar::sColision() const
{
	m_jugador->cGravedad->gravedad = m_configuracionJugador.GRAVEDAD;
	for (auto const& mosaico : m_entidades.obtenerEntidades("Mosaico")) {
		auto const superposicion = MVS2D::Fisica::CajaDelimitadora::calcularSuperposicion(m_jugador, mosaico);
		auto const superposicionAnterior = MVS2D::Fisica::CajaDelimitadora::calcularSuperposicionAnterior(m_jugador, mosaico);
		float const dy = mosaico->cMovimiento->posicion.y - m_jugador->cMovimiento->posicion.y;
		if (0 < superposicion.x && -tamanioMatriz.y < superposicion.y && dy > 0)
		{
			if (0 <= superposicion.y && superposicionAnterior.y <= 0)
			{
				m_jugador->cEntrada->puedeSaltar = true;
				m_jugador->cGravedad->gravedad = 0;
				m_jugador->cMovimiento->velocidad.y = 0;
				m_jugador->cMovimiento->posicion.y -= superposicion.y;
			}
		}
		if (0 < superposicion.x && -tamanioMatriz.y < superposicion.y && dy < 0)
		{
			if (0 <= superposicion.y && superposicionAnterior.y <= 0)
			{
				m_jugador->cMovimiento->posicion.y += superposicion.y;
				m_jugador->cMovimiento->velocidad.y = 0;
				if (mosaico->cAnimacion->animacion.obtenerNombre() == "Block") {
					std::println("Se golpea por debajo un Bloque!");
				}
			}
		}
		float const dx = mosaico->cMovimiento->posicion.x - m_jugador->cMovimiento->posicion.x;
		if (0 < superposicion.y && -tamanioMatriz.x < superposicion.x)
		{
			if (0 <= superposicion.x && superposicionAnterior.x <= 0)
			{
				if (dx > 0)
				{
					m_jugador->cMovimiento->posicion.x -= superposicion.x;
				}
				else {
					m_jugador->cMovimiento->posicion.x += superposicion.x;
				}
			}
		}
	}
	if (m_jugador->cMovimiento->posicion.y > obtenerAltoVentana())
	{
		// BUG no se actualiza el valor de la ventana
		m_jugador->cMovimiento->posicion = conversionCoordenadasAPixel(m_configuracionJugador.COORDENADA_X, m_configuracionJugador.COORDENADA_Y, m_jugador);
	}
	if (m_jugador->cMovimiento->posicion.x < m_jugador->cColisionCajaDelimitadora->tamanio.x / 2.0f)
	{
		m_jugador->cMovimiento->posicion.x = m_jugador->cColisionCajaDelimitadora->tamanio.x / 2.0f;
	}
}

void
SJugar::sRealizarAccion(
	MVS2D::Accion const& accion)
{
	if (accion.obtenerTipo() == "INICIO")
	{
		if (accion.obtenerNombre() == "PAUSA")
		{
			ponerPausa(!m_pausado);
		}
		else if (accion.obtenerNombre() == "SALIR")
		{
			alFinalizar();
		}
		else if (accion.obtenerNombre() == "SALTAR")
		{
			if (m_jugador->cEntrada->puedeSaltar)
			{
				m_jugador->cEntrada->arriba = true;
			}
		}
		else if (accion.obtenerNombre() == "ABAJO")
		{
			m_jugador->cEntrada->abajo = true;
		}
		else if (accion.obtenerNombre() == "IZQUIERDA")
		{
			m_jugador->cEntrada->izquierda = true;
		}
		else if (accion.obtenerNombre() == "DERECHA")
		{
			m_jugador->cEntrada->derecha = true;
		}
	}
	else if (accion.obtenerTipo() == "FIN")
	{
		if (accion.obtenerNombre() == "SALTAR")
		{
			m_jugador->cEntrada->arriba = false;
		}
		else if (accion.obtenerNombre() == "ABAJO")
		{
			m_jugador->cEntrada->abajo = false;
		}
		else if (accion.obtenerNombre() == "IZQUIERDA")
		{
			m_jugador->cEntrada->izquierda = false;
		}
		else if (accion.obtenerNombre() == "DERECHA")
		{
			m_jugador->cEntrada->derecha = false;
		}
	}
}


void
SJugar::sAnimacion() const
{
	if (!m_jugador->cEstado)
		return;

	if (m_jugador->cMovimiento->velocidad.y > 0)
	{
		m_jugador->cEntrada->puedeSaltar = false;
		if (m_jugador->cEstado->estadoAnterior != "Saltando")
		{
			m_jugador->cEstado->estadoAnterior = m_jugador->cEstado->estado;
			m_jugador->cEstado->estado = "Saltando";
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
			if (m_jugador->cEstado->estadoAnterior != "Corriendo")
			{
				m_jugador->cEstado->estadoAnterior = m_jugador->cEstado->estado;
				m_jugador->cEstado->estado = "Corriendo";
				m_jugador->cEstado->cambiarAnimacion = true;
			}
			else
			{
				m_jugador->cEstado->cambiarAnimacion = false;
			}
		}
		else
		{
			if (m_jugador->cEstado->estadoAnterior != "Parado")
			{
				m_jugador->cEstado->estadoAnterior = m_jugador->cEstado->estado;
				m_jugador->cEstado->estado = "Parado";
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
		std::string nombreAnimacion;
		if (m_jugador->cEstado->estado == "Parado")
		{
			nombreAnimacion = "PlayerA";
		}
		else if (m_jugador->cEstado->estado == "Saltando")
		{
			nombreAnimacion = "Jump";
		}
		else if (m_jugador->cEstado->estado == "Corriendo")
		{
			nombreAnimacion = "PlayerA";
		}
		m_jugador->cAnimacion = std::make_unique<MVS2D::Componentes::CAnimacion>(m_juego->obtenerActivos().obtenerAnimacion(nombreAnimacion), true);
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

void
SJugar::alFinalizar()
{
	// BUG no se resetea el view de la ventana
	m_juego->cambiarEscena("MENU", std::make_shared<SMenu>(m_juego));
}

void SJugar::sRenderizar()
{
	if (!m_pausado)
		m_juego->obtenerVentana().clear(sf::Color(100, 100, 255));
	else
		m_juego->obtenerVentana().clear(sf::Color(0, 255, 0));

	auto& posicionJugador = m_jugador->cMovimiento->posicion;
	float centroVentanaX = std::max(m_juego->obtenerVentana().getSize().x / 2.0f, posicionJugador.x);
	sf::View vista = m_juego->obtenerVentana().getView();
	vista.setCenter(centroVentanaX, m_juego->obtenerVentana().getSize().y - vista.getCenter().y);
	m_juego->obtenerVentana().setView(vista);

	for (auto& entidad : m_entidades.obtenerEntidades())
	{
		auto& movimiento = entidad->cMovimiento;
		if (entidad->cAnimacion)
		{
			auto& animacion = entidad->cAnimacion->animacion;
			animacion.obtenerSprite().setPosition(movimiento->posicion.x, movimiento->posicion.y);
			animacion.obtenerSprite().setScale(movimiento->escala.x, movimiento->escala.y);
			animacion.obtenerSprite().setRotation(movimiento->angulo);
			m_juego->obtenerVentana().draw(animacion.obtenerSprite());
		}
	}
}