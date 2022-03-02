#include <cmath>
#include <iostream>
#include <iomanip>
#include "maxwell_boltzmann.hpp"

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

	constexpr int N_runs = 500;
	int N_point = 10'000;
	
	for (int i = 1; i <= 100; ++i) {
		double delta_x = 0.01 * i;
		Maxwell_Boltzmann mb{seed, delta_x};

		double square_error{0.0};
		for (int i = 0; i < N_runs; ++i)
			square_error += std::pow(mb.mean(N_point) - mb.E_theor, 2);
		
		std::cout << std::fixed << std::setprecision(2) << delta_x << "\t" << std::scientific << std::setprecision(9) << std::sqrt(square_error/N_runs) << std::endl;
	}
	
	return 0;
}