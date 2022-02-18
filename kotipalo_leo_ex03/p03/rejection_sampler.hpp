#ifndef REJECTION_SAMPLER_HPP
#define REJECTION_SAMPLER_HPP
#include <random>
#include "poisson_integrator.hpp"

class Rejection_sampler : public Poisson_integrator {
	public:
		Rejection_sampler(const std::uint_fast32_t seed) : rng{seed} {};
		double integrate(const int n);
		void seed(std::uint_fast32_t seed);
	private:
		bool generate();
		static constexpr double y_min = 0.0;
		static constexpr double y_max = 0.3; // Wolfram Alpha
		std::uniform_real_distribution<double> x{a, b};
		std::uniform_real_distribution<double> y{0.0, 0.3};
		std::mt19937 rng;
};

inline double Rejection_sampler::integrate(const int n)
{
	double p = 0.0;
	for (int i = 0; i < n; ++i)
		if (generate())
			p += 1.0 / n;
	return (b - a) * (y_max - y_min) * p;
}

inline void Rejection_sampler::seed(std::uint_fast32_t seed)
{
	rng.seed(seed);
}

inline bool Rejection_sampler::generate()
{
	return y(rng) < f(x(rng));
}

#endif