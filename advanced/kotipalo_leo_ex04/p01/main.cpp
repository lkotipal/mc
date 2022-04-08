#include <cmath>
#include <iostream>
#include <random>
#include "state.hpp"

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

	double mean{0};
	double m_sq{0};

	for (int i = 0; i < trials; ++i) {
		State s = State::random_state(N, n, rng);
		double prev_mean = mean;
		double E = s.E();

		mean += (E - prev_mean) / (i + 1);
		m_sq += (E - prev_mean) * (E - mean);
	}
	std::cout << mean << " +- " << std::sqrt(m_sq / (trials - 1)) / sqrt(trials) << std::endl;

	return 0;
}