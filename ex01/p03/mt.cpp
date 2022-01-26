#include "mt.hpp"

void MT::seed(std::uint_fast32_t seed) 
{
	rng.seed(seed);
}

bool MT::has_seed(std::uint_fast32_t seed) {
	return rng == std::mt19937(seed);
}

std::uint_fast32_t MT::rand_int() 
{
	return rng();
}

std::uint_fast32_t MT::min() 
{
	return rng.min();
}

std::uint_fast32_t MT::max() 
{
	return rng.max();
}