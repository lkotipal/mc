#ifndef PM_H
#define PM_H
#include "rng.hpp"

class PM : public RNG {
public:
	PM(std::uint_fast32_t seed);
	void seed(std::uint_fast32_t seed);
	bool has_seed(std::uint_fast32_t seed);
	double rand();
private:
	std::uint_fast32_t rand_int();
	// Signed integers used for Schrage
	std::int_fast32_t state;
	static constexpr std::int_fast32_t a {16'807};	// Original Park-Miller minimal standard
	static constexpr std::int_fast32_t m {2'147'483'647};
	static constexpr std::int_fast32_t q {m / a};
	static constexpr std::int_fast32_t r {m % a};
	static constexpr std::int_fast32_t min {1};
	static constexpr std::int_fast32_t max {m - 1};
	static constexpr double inv_max {inv_max(min, max)};
};

inline PM::PM(std::uint_fast32_t seed)
{
	this->seed(seed);
}

inline void PM::seed(std::uint_fast32_t seed) 
{
	seed %= m;
	if (!seed)
		++seed;
	state = seed;
}

inline bool PM::has_seed(std::uint_fast32_t seed) 
{
	seed %= m;
	if (!seed)
		++seed;
	return state == seed;
}

inline double PM::rand()
{
	return int_to_double(min, inv_max, rand_int());
}

inline std::uint_fast32_t PM::rand_int() 
{
	// Schrage algorithm
	int32_t k = state / q;
	state = a * (state - k * q) - r * k;
	if (state < 0)
		state += m;

	return state;
}

#endif