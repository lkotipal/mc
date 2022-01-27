#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include "buffon.hpp"

int main(int argc, char *argv[]) 
{
	std::uint_fast32_t seed = 0;
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

	Buffon buffon(2.0, 10.0);
	buffon.seed(seed);

	for (int n = 10; n <= 10'000'000; n *= 10) {
		double average_error = 0.0;
		for (int i = 0; i < 100;) {
			double pi_sim = buffon.simulate(n);
			if (std::isfinite(pi_sim)) {
				average_error += fabs(pi_sim - std::numbers::pi) / 100;
				++i;
			}
		}
		std::cout << n << "\t" << average_error << std::endl;
	}
	return 0;
}