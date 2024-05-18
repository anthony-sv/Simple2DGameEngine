#include <iostream>
#include <print>
#include <boost/log/trivial.hpp>

#include "GameEngine.hpp"

int main(int argc, char** argv)
{
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	SGE2D::Math::Vector2D vec1{ 2, 4 };
	vec1 = vec1 * 2;
	std::cout << "vec1:" << vec1 << '\n';
	std::println("{}", vec1);
	GameEngine game{ "config.txt" };
	game.run();
	return 0;
}