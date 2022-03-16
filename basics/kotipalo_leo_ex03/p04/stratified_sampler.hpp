#ifndef STRATIFIED_SAMPLER_HPP
#define STRATIFIED_SAMPLER_HPP
#include "direct_sampler.hpp"

class Stratified_sampler : public Direct_sampler {
	public:
		double integrate(const int n);
	protected:
		virtual double generate(const int i, const int n);
};

inline double Stratified_sampler::integrate(const int n)
{
	double sum = 0.0;
	for (int i = 0; i < n; ++i)
		sum += (b - a) / n * generate(i, n);
	return sum;
}

inline double Stratified_sampler::generate(const int i, const int n)
{
	return f(x.rand(a + (b - a) * i / n, a + (b - a) * (i + 1) / n));
}

#endif