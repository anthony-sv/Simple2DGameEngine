#include <iostream>
#include <print>
#include <boost/log/trivial.hpp>

#include "MotorVideojuegos.hpp"

int main(int argc, char** argv)
{
	BOOST_LOG_TRIVIAL(debug) << "Leyendo activos.txt";
	MotorVideojuegos juego{ "activos.txt" };
	juego.correr();
	return 0;
}