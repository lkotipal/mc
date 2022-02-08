#ifndef QCG_H
#define QCG_H
#include <cmath>
#include "rng.hpp"

class QCG : public RNG {
public:
	QCG(std::uint_fast32_t seed);
	void seed(std::uint_fast32_t seed);
	bool has_seed(std::uint_fast32_t seed);
	double rand();
private:
	std::uint_fast32_t rand_int();
	std::uint_fast32_t state;
	static constexpr std::uint_fast32_t a {2};
	static constexpr std::uint_fast32_t b {3};
	static constexpr std::uint_fast32_t c {1};
	static constexpr std::uint_fast32_t m {0b1u << 31}; // 2^31
	static constexpr std::uint_fast32_t min {0};
	static constexpr std::uint_fast32_t max {m - 1};
};

inline QCG::QCG(std::uint_fast32_t seed)
{
	this->seed(seed);
}

inline void QCG::seed(std::uint_fast32_t seed) 
{
	state = seed % m;
}

inline bool QCG::has_seed(std::uint_fast32_t seed) 
{
	return state == seed % m;
}

inline double QCG::rand()
{
	return int_to_double(min, max, rand_int());
}

inline std::uint_fast32_t QCG::rand_int() 
{
	// Upcast to avoid overflow
	return state = (static_cast<std::uint_fast64_t>(a) * state * state + b * state + c) % m;
}

#endif