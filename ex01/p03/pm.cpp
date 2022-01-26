#include "pm.hpp"

void PM::seed(std::uint_fast32_t seed) 
{
	state = seed % m;
}

bool PM::has_seed(std::uint_fast32_t seed) 
{
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

std::uint_fast32_t PM::min() 
{
	return 1;
}

std::uint_fast32_t PM::max() 
{
	return m-1;
}