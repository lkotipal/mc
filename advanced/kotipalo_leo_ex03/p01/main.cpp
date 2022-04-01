#include <cmath>
#include <iostream>
#include "kinetic_mc.hpp"

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

	Kinetic_mc kmc {seed, 2500};

	kmc.simulate(1E9);	// 1 us = 1E9 fs
	std::cout << kmc.survival_ratio() << "\t" << kmc.jump_ratio() << std::endl;

	return 0;
}