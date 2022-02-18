#ifndef DIRECT_SAMPLER_HPP
#define DIRECT_SAMPLER_HPP
#include <random>
#include "poisson_integrator.hpp"

class Direct_sampler : public Poisson_integrator {
	public:
		Direct_sampler(const std::uint_fast32_t seed) : rng{seed} {};
		virtual double integrate(const int n);
		void seed(std::uint_fast32_t seed);
	protected:
		double generate();
		std::uniform_real_distribution<double> x{a, b};
	private:
		std::mt19937 rng;
};

inline double Direct_sampler::integrate(const int n)
{
	double sum = 0.0;
	for (int i = 0; i < n; ++i)
		sum += (b - a) / n * generate();
	return sum;
}

inline void Direct_sampler::seed(std::uint_fast32_t seed)
{
	rng.seed(seed);
}

inline double Direct_sampler::generate()
{
	return f(x(rng));
}

#endif