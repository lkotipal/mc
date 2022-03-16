#ifndef SAMPLER_HPP
#define SAMPLER_HPP
#include <random>

class Sampler {
public:
	Sampler(const std::uint_fast32_t seed) : rng{seed} {}
	double mean(const int n);
	virtual int next() = 0;
protected:
	std::mt19937 rng;
};

double Sampler::mean(const int n)
{
	int sum = 0;
	for (int i = 0; i < n; ++i)
		sum += next();
	return static_cast<double>(sum) / n;
}

#endif