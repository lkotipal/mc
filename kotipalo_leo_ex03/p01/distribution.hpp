#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP
#include <cstdint>
#include <cmath>
#include <random>

class Distribution {
public:
	Distribution(std::uint_fast32_t seed) : rng{seed} {};
	virtual double generate() = 0;
	void seed(std::uint_fast32_t seed);
protected:
	double f(double x);
	double generate_uniform();
private:
	std::mt19937 rng;
	std::uniform_real_distribution<double> dis{0.0, 1.0};
};

inline void Distribution::seed(std::uint_fast32_t seed)
{
	rng.seed(seed);
}

inline double Distribution::f(double x)
{
	return 1 / (x * x + 4) / std::atan(5);
}

inline double Distribution::generate_uniform()
{
	return dis(rng);
}

#endif