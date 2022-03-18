#include <cmath>
#include <iostream>
#include "self_avoiding_walker.hpp"

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

	constexpr int n_trials = 100'000;
	Self_avoiding_walker saw{0};

	// For step size greater than 10000 double precision isn't enough for weights
	for (int n_steps = 1; n_steps <= 8192; n_steps *= 2) {
		double sum_r{0};
		double sum_w{0};

		double mean{0};
		double m_sq{0};

		std::vector<double> weights(n_trials);

		for (int i = 0; i < n_trials; ++i) {
			Walker_result result = saw.simulate(n_steps);
			double prev_mean = mean;

			// For calculating weighted mean
			sum_r += result.r_squared * result.weight;
			sum_w += result.weight;

			// For calculating standard deviation
			weights[i] = result.weight;
			mean += (result.r_squared - mean) / (i + 1);
			m_sq += (result.r_squared - prev_mean) * (result.r_squared - mean);
		}

		// Variance
		double w_squared{0};
		for (double w : weights) {
			w_squared += std::pow(w / sum_w, 2);
		}

		std::cout << std::scientific << n_steps << "\t" << sum_r / sum_w << "\t" << std::sqrt(m_sq / (n_trials - 1) * w_squared) << std::endl;
		//std::cout << std::scientific << n_steps << "\t" << mean << "\t" << std::sqrt(m_sq / (n_trials - 1)) / sqrt(n_trials) << std::endl;
	}

	//for (int i = 0; i < n_trials; ++i) {
	//	Walker_result result = saw.simulate(50);
	//	std::cout << result.r_squared << "\t" << result.weight << std::endl;
	//}
	
	return 0;
}