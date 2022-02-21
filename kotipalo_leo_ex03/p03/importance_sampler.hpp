#ifndef IMPORTANCE_SAMPLER_HPP
#define IMPORTANCE_SAMPLER_HPP
#include <random>
#include "poisson_integrator.hpp"

class Importance_sampler : public Poisson_integrator {
	public:
		Importance_sampler(const std::uint_fast32_t seed) : Poisson_integrator{seed} {};
		virtual double integrate(const int n);
		static constexpr double g(const double x);
	private:
		static constexpr double lambda = 2;
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
	return (1 - std::exp(-20.0 * lambda)) * lambda * std::exp(-lambda * x); // Correction term very small
}

inline double Importance_sampler::generate()
{
	double x = this->x(rng);
	return f(x) / g(x);
}

#endif