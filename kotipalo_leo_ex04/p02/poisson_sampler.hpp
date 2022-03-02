#ifndef POISSON_SAMPLER_HPP
#define POISSON_SAMPLER_HPP
#include "sampler.hpp"

class Poisson_sampler : public Sampler {
public:
	Poisson_sampler(const std::uint_fast32_t seed) : Sampler{seed} {};
	int next();
private:
	std::poisson_distribution<int> dis{3};
};

inline int Poisson_sampler::next()
{
	return dis(rng);
}

#endif