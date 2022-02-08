#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <numbers>
#include <string>
#include "../p01/rng.hpp"
#include "lcg.hpp"
#include "mt.hpp"
#include "pm.hpp"
#include "../p01/qcg.hpp"

void rng_test(RNG& rng, unsigned int n, std::string out_name)
{
	std::ofstream out_file{out_name};

	for (int i = 0; i < n; ++i)
		if (out_file.is_open())
			out_file << rng.rand() << std::endl;
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
	MT mt{seed};
	QCG qcg{seed};
	rng_test(lcg, 1'000'000, "lcg.txt");
	rng_test(pm, 1'000'000, "pm.txt");
	rng_test(mt, 1'000'000, "mt.txt");
	rng_test(qcg, 1'000'000, "qcg.txt");

	return 0;
}