#include <array>
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

void rng_test(RNG& rng, int tests, int points, std::string out_name)
{
	std::ofstream out_file{out_name};

	for (int i = 0; i < tests; ++i) {
		constexpr int M = 100;
		std::array<int, M> bins{};
		for (int j = 0; j < points; ++j)
			bins[static_cast<int>(rng.rand() * 100)] += 1;

		double chi_squared = 0;
		double m_i = static_cast<double>(points) / M;
		for (int j : bins)
			chi_squared += std::pow(j - m_i, 2)/m_i;

		if (out_file.is_open())
			out_file << chi_squared << std::endl;
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
	MT mt{seed};
	QCG qcg{seed};
	constexpr int tests = 10'000;
	constexpr int points = 1'000'000;
	rng_test(lcg, tests, points, "lcg.txt");
	rng_test(pm, tests, points, "pm.txt");
	rng_test(mt, tests, points, "mt.txt");
	rng_test(qcg, tests, points, "qcg.txt");

	return 0;
}