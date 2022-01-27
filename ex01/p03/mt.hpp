#ifndef MT_H
#define MT_H
#include "rng.hpp"
#include <random>

class MT : public RNG<0, std::numeric_limits<uint32_t>::max()> {
public:
	void seed(std::uint_fast32_t seed);
	bool has_seed(std::uint_fast32_t seed);
private:
	std::uint_fast32_t rand_int();
	std::mt19937 rng {1};
};

inline void MT::seed(std::uint_fast32_t seed) 
{
	rng.seed(seed);
}

inline bool MT::has_seed(std::uint_fast32_t seed) 
{
	return rng == std::mt19937(seed);
}

inline std::uint_fast32_t MT::rand_int() 
{
	return rng();
}

#endif