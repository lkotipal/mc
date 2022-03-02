#ifndef DISCRETE_SAMPLER_HPP
#define DISCRETE_SAMPLER_HPP
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "sampler.hpp"

class Discrete_sampler : public Sampler {
public:
	Discrete_sampler(const std::uint_fast32_t seed);
	int next();
private:
	std::unique_ptr<std::discrete_distribution<int>> dis;
	std::vector<int> x;
};

inline int Discrete_sampler::next()
{
	return x[(*dis)(rng)];
}

inline Discrete_sampler::Discrete_sampler(const std::uint_fast32_t seed) : Sampler{seed} 
{
	std::vector<int> n;
	std::ifstream file("distr1.dat");
	if (file.is_open()) {
		int next_x;
		int next_n;
		while (file >> next_x >> next_n) {
			x.push_back(next_x);
			n.push_back(next_n);
		}
	}
	dis = std::make_unique<std::discrete_distribution<int>>(n.begin(), n.end());
}

#endif