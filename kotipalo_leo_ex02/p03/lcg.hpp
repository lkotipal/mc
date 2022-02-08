#ifndef LCG_H
#define LCG_H
#include "../p01/rng.hpp"

class LCG : public RNG {
public:
	LCG(std::uint_fast32_t seed);
	void seed(std::uint_fast32_t seed);
	bool has_seed(std::uint_fast32_t seed);
	double rand();
private:
	std::uint_fast32_t rand_int();
	std::uint_fast32_t state;
	static constexpr std::uint_fast32_t a {3'557'181};
	static constexpr std::uint_fast32_t c {1};
	static constexpr std::uint_fast32_t m {113'829'760};
	static constexpr std::int_fast32_t min {0};
	static constexpr std::int_fast32_t max {m - 1};
};

inline LCG::LCG(std::uint_fast32_t seed)
{
	this->seed(seed);
}

inline void LCG::seed(std::uint_fast32_t seed) 
{
	state = seed % m;
}

inline bool LCG::has_seed(std::uint_fast32_t seed) 
{
	return state == seed % m;
}

inline double LCG::rand()
{
	return int_to_double(min, max, rand_int());
}

inline std::uint_fast32_t LCG::rand_int() 
{
	// Upcast to avoid overflow
	return state = (static_cast<std::uint_fast64_t>(a) * state + c) % m;
}

#endif