#ifndef IMPORTANCE_SAMPLER_HPP
#define IMPORTANCE_SAMPLER_HPP
#include <random>
#include "Direct_sampler.hpp"

class Importance_sampler : public Direct_sampler {
	public:
		Importance_sampler(const std::uint_fast32_t seed) : Direct_sampler{seed} {};
		virtual double integrate(const int n);
		static constexpr double g(const double x);
	private:
		static constexpr double lambda = 1;
		double generate();
		std::exponential_distribution<double> x{lambda};
};

inline double Importance_sampler::integrate(const int n)
{
	double sum = 0.0;
	for (int i = 0; i < n; ++i)
		sum += generate();
	return sum / n;
}

inline constexpr double Importance_sampler::g(const double x)
{
	return lambda * std::exp(-lambda * x) / (1 - std::exp(-b * lambda)); // Correction term very small
}

inline double Importance_sampler::generate()
{
	double x;
	do 
		x = this->x(rng);
	while (x > b);
	return f(x) / g(x);
}

#endif