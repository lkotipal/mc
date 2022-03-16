#ifndef REJECTION_SAMPLER_HPP
#define REJECTION_SAMPLER_HPP
#include <random>
#include "poisson_integrator.hpp"

class Rejection_sampler : public Poisson_integrator {
	public:
		Rejection_sampler(const std::uint_fast32_t seed) : Poisson_integrator{seed} {};
		double integrate(const int n);
	private:
		bool generate();
		static constexpr double y_min = 0.0;
		static constexpr double y_max = 0.3; // Wolfram Alpha
		std::uniform_real_distribution<double> y{0.0, 0.3};
};

inline double Rejection_sampler::integrate(const int n)
{
	int hits = 0;
	for (int i = 0; i < n; ++i)
		hits += generate();
	return (b - a) * (y_max - y_min) * hits / n;
}

inline bool Rejection_sampler::generate()
{
	return y(rng) < f(x(rng));
}

#endif