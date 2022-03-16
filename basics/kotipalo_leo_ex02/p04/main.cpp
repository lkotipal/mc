#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <numbers>
#include <string>
#include "../p01/rng.hpp"
#include "../p03/lcg.hpp"
#include "../p03/pm.hpp"
#include "shuffler.hpp"

void rng_test(RNG& rng, unsigned int n, std::string out_name)
{
	std::ofstream out_file{out_name};

	for (int i = 0; i < n; ++i)
		if (out_file.is_open())
			out_file << rng.rand(0, 1.0) << std::endl;
}

void rng_test_small(RNG& rng, unsigned int n, std::string out_name)
{
	std::ofstream out_file{out_name};

	double x, y;
	for (int i = 0; i < n; ++i) {
		do {
			x = rng.rand(-1.0, 1.0);
			y = rng.rand(-1.0, 1.0);
		} while (fabs(x) > 0.01 || fabs(y) > 0.01);
		if (out_file.is_open())
			out_file << x << "\t" << y << std::endl;
	}
}

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

	LCG lcg{seed};
	PM pm{seed};
	Shuffler shuffler{seed};
	constexpr int n = 100'000;
	rng_test(lcg, n, "lcg.txt");
	rng_test(pm, n, "pm.txt");
	rng_test(shuffler, n, "shuffler.txt");

	return 0;
}