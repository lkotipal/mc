#ifndef DIRECT_SAMPLER_HPP
#define DIRECT_SAMPLER_HPP
#include "poisson_integrator.hpp"

class Direct_sampler : public Poisson_integrator {
	public:
		virtual double integrate(const int n);
	protected:
		double generate();
};

inline double Direct_sampler::integrate(const int n)
{
	double sum = 0.0;
	for (int i = 0; i < n; ++i)
		sum += generate();
	return (b - a) / n * sum;
}

inline double Direct_sampler::generate()
{
	return f(x.rand(a, b));
}

#endif