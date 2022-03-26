#include <cmath>
#include <iostream>
#include "scattering_simulator.hpp"

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

	constexpr int trajectories{2000};
	constexpr int trials{100};
	Scattering_simulator ss{seed};

	double mean{0};
	double m_sq{0};
	for (int i = 0; i < trials; ++i) {
		double x =  ss.simulate(trajectories);
		double prev_mean = mean;

		mean += (x - mean) / (i + 1);
		m_sq += (x - prev_mean) * (x - mean);
	}

	std::cout << std::scientific << mean << " +- " << std::sqrt(m_sq / (trials - 1)) / sqrt(trials) << std::endl;

	return 0;
}