#ifndef MT_H
#define MT_H
#include "rng.hpp"

class MT : public RNG {
public:
	void seed(std::uint_fast32_t seed);
	bool has_seed(std::uint_fast32_t seed);
	std::uint_fast32_t min();
	std::uint_fast32_t max();
private:
	std::uint_fast32_t rand_int();
	std::mt19937 rng;
};

#endif