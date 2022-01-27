#ifndef RNG_H
#define RNG_H
#include <cstdint>

class RNG {
public:
	virtual void seed(std::uint_fast32_t seed) = 0;
	virtual bool has_seed(std::uint_fast32_t seed) = 0;
	virtual double rand() = 0;
	double rand(double range_min, double range_max);
};

inline double RNG::rand(double range_min, double range_max)
{
	return range_min + (range_max - range_min) * rand();
}

static constexpr double inv_max(std::uint_fast32_t min, std::uint_fast32_t max)
{
	return 1.0 / (max - min);
}

static inline double int_to_double(std::uint_fast32_t min, double inv_max, std::uint_fast32_t i)
{
	return (i - min) * inv_max;
}

#endif