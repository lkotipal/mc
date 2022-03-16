#include <cassert>
#include <fstream>
#include <iostream>
#include "inversion_distribution.hpp"
#include "sampling_distribution.hpp"

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

	Inversion_distribution id{seed};
	Sampling_distribution sd{seed};

	std::ofstream out_inversion{"inversion.txt"};
	for (int i = 0; i < 1'000'000; ++i) {
		double d = id.generate();
		assert(d >= -10 && d <= 10);
		if (out_inversion.is_open())
			out_inversion << d << std::endl;
	}

	std::ofstream out_sampling{"sampling.txt"};
	for (int i = 0; i < 1'000'000; ++i) {
		double d = sd.generate();
		assert(d >= -10 && d <= 10);
		if (out_sampling.is_open())
			out_sampling << d << std::endl;
	}
	
	return 0;
}