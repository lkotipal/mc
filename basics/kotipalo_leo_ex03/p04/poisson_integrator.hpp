#ifndef POISSON_INTEGRATOR_HPP
#define POISSON_INTEGRATOR_HPP
#include <cstdint>
#include <cmath>
#include "vdc.hpp"

class Poisson_integrator {
	public:
		virtual double integrate(const int n) = 0;
		void seed(const std::uint_fast32_t seed);
		static constexpr double f(const double x);
		static constexpr double a = 0.0;
		static constexpr double b = 20.0;
		static constexpr double lambda = 2.0;
	protected:
		VDC x{13};
};

inline constexpr double Poisson_integrator::f(const double x)
{
	return std::exp(x * std::log(lambda) - lambda - std::lgamma(x + 1));
}

#endif