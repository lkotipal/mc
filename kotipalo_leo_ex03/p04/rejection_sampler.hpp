#ifndef REJECTION_SAMPLER_HPP
#define REJECTION_SAMPLER_HPP
#include "poisson_integrator.hpp"

class Rejection_sampler : public Poisson_integrator {
	public:
		double integrate(const int n);
	private:
		bool generate();
		static constexpr double y_min = 0.0;
		static constexpr double y_max = 0.3; // Wolfram Alpha
		VDC y{17};
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
	return y.rand(y_min, y_max) < f(x.rand(a, b));
}

#endif