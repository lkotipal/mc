#ifndef STRATIFIED_SAMPLER_HPP
#define STRATIFIED_SAMPLER_HPP
#include "direct_sampler.hpp"

class Stratified_sampler : public Direct_sampler {
	public:
		Stratified_sampler(const std::uint_fast32_t seed) : Direct_sampler{seed} {};
		double integrate(const int n);
	protected:
		virtual void set_bin(int i, int n);
};

inline double Stratified_sampler::integrate(const int n)
{
	double sum = 0.0;
	for (int i = 0; i < n; ++i) {
		set_bin(i, n);
		sum += (b - a) / n * generate();
	}
	return sum;
}

inline void Stratified_sampler::set_bin(int i, int n)
{
	x = std::uniform_real_distribution<double>(a + (b - a) * i / n, a + (b - a) * (i + 1) / n);
}

#endif