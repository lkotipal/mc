#include <cmath>
#include <iostream>
#include <random>
#include "../p01/state.hpp"

int main(int argc, char *argv[]) 
{
	std::uint_fast32_t seed = 1;
	if (argc > 1) {
		try {
			seed = std::stoi(argv[1]);
		} catch (std::invalid_argument e) {
			std::clog << "Invalid seed given." << std::endl;
		}
	} else {
		std::clog << "No seed given." << std::endl;
	}
	std::clog << "Using seed " << seed << std::endl;
	std::mt19937 rng {seed};

	constexpr int trials {20};
	constexpr int N {500};
	constexpr int n {1000};

	State s = State::random_state(N, n, rng);
	State s2 = s.swap(rng);

	std::cout << s.N() << "\t" << s2.N() << std::endl;
	std::cout << s.E() << "\t" << s2.E() << std::endl;

	return 0;
}