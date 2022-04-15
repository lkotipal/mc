#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "maxwell_boltzmann.hpp"
#include "../p01/state.hpp"

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

	constexpr int trials {1'000'000};
	constexpr int N {500};
	constexpr int n {1000};

	std::cout << "T\tE_1\tE_2\tE_3\tAve" << std::endl;

	std::array<double, 3> temps {300, 2'000, 10'000};
	std::array<std::string, 3> names {"300.tsv", "2000.tsv", "10000.tsv"};

	for (int i = 0; i < 3; ++i) {
		double T {temps[i]};
		Maxwell_Boltzmann mb{T, seed};
		std::vector<int> v_total(n, 0);

		std::array<double, 3> means{0.0};
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < trials; ++k) {
				State s {mb.next_state()};
				double prev_mean = means[j];
				double E = s.E();

				means[j] += (E - prev_mean) / (k + 1);
				for (int l = 0; l < n; ++l)
					v_total[l] += s[l];
			}
		}
		std::cout << T << "\t" << means[0] << "\t" << means[1] << "\t" << means[2] << "\t" << (means[0] + means[1] + means[2])/3 << std::endl;

		std::ofstream f;
		f.open(names[i]);
		for (int i : v_total)
			f << static_cast<double>(i) / (3 * trials) << std::endl;
	}

	return 0;
}