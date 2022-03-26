#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include "../p01/radiation_simulator.hpp"
#include "../p02/scattering_simulator.hpp"
#include "better_scattering_simulator.hpp"

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
	std::array<std::unique_ptr<Radiation_simulator>, 2> simulators {
		std::make_unique<Scattering_simulator>(seed), 
		std::make_unique<Better_scattering_simulator>(seed)
	};

	std::cout << "N\tScattering\tStd. error\tOptimized\t Std. error" << std::endl;
	for (int trajectories : {10, 20, 50, 40, 80, 100, 200, 500, 1000, 2000})
	{
		std::array<double, 2> means {0.0, 0.0};
		std::array<double, 2> m_sqs {0.0, 0.0};
		for (int sim = 0; sim < simulators.size(); ++sim) {
			for (int i = 0; i < trials; ++i) {
				double x =  simulators[sim]->simulate(trajectories);
				double prev_mean = means[sim];

				means[sim] += (x - means[sim]) / (i + 1);
				m_sqs[sim] += (x - prev_mean) * (x - means[sim]);
			}
		}

		std::cout << trajectories;
		for (int sim = 0; sim < simulators.size(); ++sim) {
			std::cout << "\t" << std::scientific << means[sim] << "\t" << std::sqrt(m_sqs[sim] / (trials - 1) / sqrt(trials));
		}
		std::cout << std::endl;
	}

	return 0;
}