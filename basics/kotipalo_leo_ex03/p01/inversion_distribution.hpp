#ifndef INVERSION_DISTRIBUTION_HPP
#define INVERSION_DISTRIBUTION_HPP
#include <cmath>
#include "distribution.hpp"

class Inversion_distribution : public Distribution
{
public:
	Inversion_distribution(std::uint_fast32_t seed) : Distribution{seed} {};
	double generate();
};

inline double Inversion_distribution::generate()
{
	return 2 * std::tan(2 * generate_uniform() * std::atan(5) - std::atan(5));
}

#endif