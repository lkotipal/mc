#include <cmath>
#include <iostream>
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

	int l_1 = 1;
	int l_2 = 2;
	if (argc > 3) {
		try {
			l_1 = std::stoi(argv[2]);
			l_2 = std::stoi(argv[3]);
		} catch (std::invalid_argument e) {
			std::clog << "Invalid step lengths given." << std::endl;
		}
	} else {
		std::clog << "No step length given." << std::endl;
	}
	std::clog << "Using step lengths " << l_1 << ", " << l_2 << std::endl;

	constexpr int n_trials = 1'000;
	Random_walker rw{0, l_1, l_2};

	for (int n_steps = 1; n_steps <= 1'048'576; n_steps *= 2) {
		double mean = 0;
		double m_sq = 0;

		for (int i = 0; i < n_trials; ++i) {
			int x = rw.simulate(n_steps);
			double prev_mean = mean;

			mean += (x - mean) / (i + 1);
			m_sq += (x - prev_mean) * (x - mean);
		}

		std::cout << std::scientific << n_steps << "\t" << mean << "\t" << std::sqrt(m_sq / (n_trials - 1)) / sqrt(n_trials) << std::endl;
	}
	
	return 0;
}