#ifndef IMPORTANCE_SAMPLER_HPP
#define IMPORTANCE_SAMPLER_HPP
#include "direct_sampler.hpp"

class Importance_sampler : public Direct_sampler {
	public:
		virtual double integrate(const int n);
		static constexpr double g(const double x);
	private:
		static constexpr double lambda = 1;
		double generate();
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
		x = -std::log(this->x.rand()) / lambda;
	while (x > b);
	return f(x) / g(x);
}

#endif