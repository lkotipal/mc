#ifndef MT_H
#define MT_H
#include "rng.hpp"

class MT : public RNG<0, std::numeric_limits<uint32_t>::max()> {
public:
	void seed(std::uint_fast32_t seed);
	bool has_seed(std::uint_fast32_t seed);
private:
	std::uint_fast32_t rand_int();
	std::mt19937 rng;
};

#endif