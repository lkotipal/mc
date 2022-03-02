#include <cmath>
#include <fstream>
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
	constexpr double delta_E{0.19};	// From testing
	Maxwell_Boltzmann mb{seed, delta_E};
	
	for (int N_point = 100; N_point <= 100'000'000; N_point *= 10) {
		double square_error{0.0};
		for (int i = 0; i < N_runs; ++i)
			square_error += std::pow(mb.mean(N_point) - mb.E_theor, 2);
		
		std::cout << std::scientific << std::setprecision(0) << static_cast<double>(N_point) << "\t" << std::setprecision(9) << std::sqrt(square_error/N_runs) << std::endl;
	}
	
	return 0;
}