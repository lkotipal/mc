#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <numbers>
#include <string>
#include "../p03/rng.hpp"
#include "../p03/lcg.hpp"
#include "../p03/mt.hpp"
#include "../p03/pm.hpp"
#include "buffon.hpp"

void rng_test(std::unique_ptr<RNG> rng, unsigned int n, std::string out_name)
{
	std::ofstream out_file{out_name};

	for (int i = 0; i < n; ++i)
		if (out_file.is_open())
			out_file << rng->rand(-1.0, 1.0) << "\t" << rng->rand(-1.0, 1.0) << std::endl;
}

void rng_test_small(std::unique_ptr<RNG> rng, unsigned int n, std::string out_name)
{
	std::ofstream out_file{out_name};

	for (int i = 0; i < n; ++i) {
		double x;
		do {
			x = rng->rand(-1.0, 1.0);
		} while (fabs(x) > 0.01);
		double y;
		do {
			y = rng->rand(-1.0, 1.0);
		} while (fabs(y) > 0.01);
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

	rng_test(std::unique_ptr<RNG>(new LCG(seed)), 100, "lcg_100.txt");
	rng_test(std::unique_ptr<RNG>(new LCG(seed)), 10'000, "lcg_10000.txt");
	rng_test(std::unique_ptr<RNG>(new PM(seed)), 100, "pm_100.txt");
	rng_test(std::unique_ptr<RNG>(new PM(seed)), 10'000, "pm_10000.txt");
	rng_test(std::unique_ptr<RNG>(new MT(seed)), 100, "mt_100.txt");
	rng_test(std::unique_ptr<RNG>(new MT(seed)), 10'000, "mt_10000.txt");

	rng_test_small(std::unique_ptr<RNG>(new LCG(seed)), 100, "lcg_small_100.txt");
	rng_test_small(std::unique_ptr<RNG>(new LCG(seed)), 10'000, "lcg_small_10000.txt");
	rng_test_small(std::unique_ptr<RNG>(new PM(seed)), 100, "pm_small_100.txt");
	rng_test_small(std::unique_ptr<RNG>(new PM(seed)), 10'000, "pm_small_10000.txt");
	rng_test_small(std::unique_ptr<RNG>(new MT(seed)), 100, "mt_small_100.txt");
	rng_test_small(std::unique_ptr<RNG>(new MT(seed)), 10'000, "mt_small_10000.txt");

	Buffon buffon(2, 10, new LCG(seed));
	double average_error = 0.0;
	for (int i = 0; i < 100;) {
		double pi_sim = buffon.simulate(10000);
		if (std::isfinite(pi_sim)) {
			average_error += fabs(pi_sim - std::numbers::pi) / 100;
			++i;
		}
	}
	std::cout << 10000 << "\t" << average_error << std::endl;

	return 0;
}