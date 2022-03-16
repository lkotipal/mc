#ifndef POISSON_INTEGRATOR_HPP
#define POISSON_INTEGRATOR_HPP
#include <cstdint>
#include <cmath>
#include <random>

class Poisson_integrator {
	public:
		Poisson_integrator(std::uint_fast32_t seed) : rng{seed} {};
		virtual double integrate(const int n) = 0;
		void seed(const std::uint_fast32_t seed);
		static constexpr double f(const double x);
		static constexpr double a = 0.0;
		static constexpr double b = 20.0;
		static constexpr double lambda = 2.0;
	protected:
		std::mt19937 rng;
		std::uniform_real_distribution<double> x{a, b};

};

inline void Poisson_integrator::seed(std::uint_fast32_t seed)
{
	rng.seed(seed);
}

inline constexpr double Poisson_integrator::f(const double x)
{
	return std::exp(x * std::log(lambda) - lambda - std::lgamma(x + 1));
}

#endif