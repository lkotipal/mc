#include <cmath>
#include <iostream>
#include <set>
#include "random_walker.hpp"

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

	constexpr int n_trials = 10'000;
	Random_walker rw{0};

	for (int i = 0; i < n_trials; ++i)
		std::cout << rw.simulate() << std::endl;
	
	return 0;
}