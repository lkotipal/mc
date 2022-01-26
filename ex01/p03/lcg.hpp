#ifndef LCG_H
#define LCG_H
#include "rng.hpp"

class LCG : public RNG {
public:
	void seed(std::uint_fast32_t seed);
	bool has_seed(std::uint_fast32_t seed);
	std::uint_fast32_t min();
	std::uint_fast32_t max();
private:
	std::uint_fast32_t rand_int();
	static constexpr std::uint_fast32_t a = 3'557'181;
	static constexpr std::uint_fast32_t c = 3;
	static constexpr std::uint_fast32_t m = 113'829'760;
	std::linear_congruential_engine<std::uint_fast32_t, 3'557'181, 3, 113'829'760> rng;
};

#endif