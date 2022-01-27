#ifndef PM_H
#define PM_H
#include "rng.hpp"

class PM : public RNG<1, 2'147'483'647 - 1> {
public:
	void seed(std::uint_fast32_t seed);
	bool has_seed(std::uint_fast32_t seed);
private:
	std::uint_fast32_t rand_int();
	// Signed integers used for Schrage
	std::int_fast32_t state {1};
	static constexpr std::int_fast32_t a {16'807};	// Original Park-Miller minimal standard
	static constexpr std::int_fast32_t m {2'147'483'647};
	static constexpr std::int_fast32_t q {m / a};
	static constexpr std::int_fast32_t r {m % a};
};

#endif