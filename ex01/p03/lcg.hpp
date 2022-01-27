#ifndef LCG_H
#define LCG_H
#include "rng.hpp"

class LCG : public RNG<0, 113'829'760 - 1> {
public:
	void seed(std::uint_fast32_t seed);
	bool has_seed(std::uint_fast32_t seed);
private:
	std::uint_fast32_t rand_int();
	std::uint_fast32_t state {1};
	static constexpr std::uint_fast32_t a {3'557'181};
	static constexpr std::uint_fast32_t c {3};
	static constexpr std::uint_fast32_t m {113'829'760};
};

inline void LCG::seed(std::uint_fast32_t seed) 
{
	this->state = seed % m;
}

inline bool LCG::has_seed(std::uint_fast32_t seed) 
{
	return this->state == seed % m;
}

inline std::uint_fast32_t LCG::rand_int() 
{
	// Upcast to avoid overflow
	return this->state = (static_cast<std::uint_fast64_t>(a) * this->state + c) % m;
}

#endif