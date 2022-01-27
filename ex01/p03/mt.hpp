#ifndef MT_H
#define MT_H
#include "rng.hpp"
#include <random>

class MT : public RNG {
public:
	MT(std::uint_fast32_t seed) : rng {seed} {}
	void seed(std::uint_fast32_t seed);
	bool has_seed(std::uint_fast32_t seed);
	double rand();
private:
	std::uint_fast32_t rand_int();
	std::mt19937 rng;
	static constexpr std::uint_fast32_t min {0};
	static constexpr std::uint_fast32_t max {std::numeric_limits<uint32_t>::max()};
	static constexpr double inv_max {inv_max(min, max)};
};

inline void MT::seed(std::uint_fast32_t seed) 
{
	rng.seed(seed);
}

inline bool MT::has_seed(std::uint_fast32_t seed) 
{
	return rng == std::mt19937(seed);
}

inline double MT::rand()
{
	return int_to_double(min, inv_max, rand_int());
}

inline std::uint_fast32_t MT::rand_int() 
{
	return rng();
}

#endif