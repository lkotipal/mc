#include <cmath>
#include <iostream>
#include "sphere.hpp"

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

	Sphere sphere(seed);

	constexpr int n = 100'000'000;
	std::cout << std::fixed;
	for (int d = 1; d < 16; ++d) {
		double p = sphere.simulate(d, n);
		double err = std::sqrt((p - p*p) / n);
		double V = pow(2, d);
		std::cout << d << ":\t" << V * p << " +- " << V * err << std::endl;
	}
	
	return 0;
}