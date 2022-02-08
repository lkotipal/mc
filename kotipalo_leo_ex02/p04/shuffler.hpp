#ifndef SHUFFLER_H
#define SHUFFLER_H
#include <array>
#include "../p01/rng.hpp"
#include "../p03/lcg.hpp"

class Shuffler : public RNG {
public:
	Shuffler(std::uint_fast32_t seed);
	void seed(std::uint_fast32_t seed);
	bool has_seed(std::uint_fast32_t seed);
	double rand();
private:
	LCG lcg;
	std::uint_fast32_t rand_int();
	std::uint_fast32_t lcg_int(std::uint_fast64_t state);
	static constexpr std::uint_fast32_t m {113'829'760};
	static constexpr std::uint_fast32_t min {0};
	static constexpr std::uint_fast32_t max {m - 1};
	static constexpr int NTAB = 32;
	std::uint_fast32_t iy{0};
	std::array<uint_fast32_t, NTAB> iv{};
};

inline Shuffler::Shuffler(std::uint_fast32_t seed) : lcg(seed)
{
	this->seed(seed);
}

inline void Shuffler::seed(std::uint_fast32_t seed) 
{
	lcg.seed(seed);
	// Discard first 8 numbers
	for (int i = 0; i < 8; ++i)
		lcg.rand();
	
	// Initialize array
	for (int i : iv) {
		iy = lcg.rand_int();
		i = iy;
	}
	
}

inline bool Shuffler::has_seed(std::uint_fast32_t seed) 
{
	Shuffler other{seed};
	for (int i = 0; i < NTAB; ++i)
		if (iv[i] != other.iv[i])
			return false;
	return true;
}

inline double Shuffler::rand()
{
	return int_to_double(min, max, rand_int());
}

inline std::uint_fast32_t Shuffler::rand_int()
{
	lcg.seed(iy);
	const std::uint_fast32_t next_int = lcg.rand_int();
	const int j = iy / (1 + max / NTAB);
	iy = iv[j];
	iv[j] = next_int;
	return iy;
}

#endif