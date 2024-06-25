#pragma once
#include "MotorVideojuegos.hpp"
#include "Accion.hpp"
#include "ManejadorEntidades.hpp"

class MotorVideojuegos;
namespace MVS2D::Escenas
{
	class Escena
	{
	public:
		virtual void actualizar() = 0;
		virtual void sRealizarAccion(Accion const& accion) = 0;
		virtual void sRenderizar() = 0;

		[[nodiscard]] Escena() = default;
		[[nodiscard]] explicit Escena(MotorVideojuegos* motorVideojuegos);
		//virtual ~Escena();

		virtual void realizarAccion(Accion const& accion);
		void registrarAccion(int teclaEntrada, std::string const& nombre);
		std::unordered_map<int, std::string> const& obtenerMapaAcciones() const;
		std::size_t obtenerFrameActual() const;
		bool finalizo() const;
		std::size_t obtenerAnchoVentana() const;
		std::size_t obtenerAltoVentana() const;

	protected:
		MotorVideojuegos* m_juego{ nullptr };
		Entidades::ManejadorEntidades m_entidades;
		std::size_t m_frameActual{ 0 };
		std::unordered_map<int, std::string> m_acciones;
		bool m_pausado{ false };
		bool m_finalizo{ false };
		virtual void alFinalizar() = 0;
		void ponerPausa(bool const pausa);
	};
}