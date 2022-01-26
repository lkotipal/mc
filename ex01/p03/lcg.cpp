#include "lcg.hpp"

void LCG::seed(std::uint_fast32_t seed) 
{
	rng.seed(seed);
}

bool LCG::has_seed(std::uint_fast32_t seed) 
{
	return rng == std::linear_congruential_engine<std::uint_fast32_t, 3'557'181, 3, 113'829'760>(seed);
}

std::uint_fast32_t LCG::rand_int() 
{
	return rng();
}