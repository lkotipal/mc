#include "pm.hpp"

void PM::seed(std::uint_fast32_t seed) 
{
	seed %= m;
	if (!seed)
		++seed;
	state = seed;
}

bool PM::has_seed(std::uint_fast32_t seed) 
{
	seed %= m;
	if (!seed)
		++seed;
	return state == seed;
}

std::uint_fast32_t PM::rand_int() 
{
	// Schrage algorithm
	int32_t k = state / q;
	state = a * (state - k * q) - r * k;
	if (state < 0)
		state += m;

	return state;
	// state in [1, m-1]
	return (double) (state - 1) / (m - 1);
}