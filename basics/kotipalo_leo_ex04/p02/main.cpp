#include <cmath>
#include <iostream>
#include <iomanip>
#include "sampler.hpp"
#include "discrete_sampler.hpp"
#include "poisson_sampler.hpp"

void test_sampler(Sampler& s, const std::string& filename, const int n)
{
	std::ofstream file(filename);
	for (int i = 0; i < 1'000'000; ++i)
		if (file.is_open())
			file << std::fixed << s.mean(n) << std::endl;
}

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

	Discrete_sampler ds{seed};
	Poisson_sampler ps{seed};
	constexpr int n_points = 100;

	test_sampler(ds, "discrete.tsv", n_points);
	test_sampler(ps, "poisson.tsv", n_points);
	
	return 0;
}