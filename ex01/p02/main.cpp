#include <cmath>
#include <iostream>
#include <numbers>
#include "buffon.hpp"

int main() 
{
	Buffon buffon(2.0, 10.0);
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