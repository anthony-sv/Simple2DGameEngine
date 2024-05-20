#include <iostream>
#include <print>
#include <boost/log/trivial.hpp>

#include "GameEngine.hpp"

int main(int argc, char** argv)
{
	BOOST_LOG_TRIVIAL(debug) << "Reading assets.txt";
	GameEngine game{ "assets.txt" };
	game.run();
	return 0;
}