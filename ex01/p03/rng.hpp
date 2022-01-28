#ifndef RNG_H
#define RNG_H
#include <cstdint>

class RNG {
public:
	virtual void seed(std::uint_fast32_t seed) = 0;
	virtual bool has_seed(std::uint_fast32_t seed) = 0;
	virtual double rand() = 0;
	double rand(double range_min, double range_max);
protected:
	static constexpr double inv_max(std::uint_fast32_t min, std::uint_fast32_t max);
	static constexpr double int_to_double(std::uint_fast32_t min, std::uint_fast32_t max, std::uint_fast32_t i);
};

inline double RNG::rand(double range_min, double range_max)
{
	return range_min + (range_max - range_min) * rand();
}

inline constexpr double RNG::inv_max(std::uint_fast32_t min, std::uint_fast32_t max)
{
	// 1.0 non-inclusive
	return 1.0 / (static_cast<std::uint_fast64_t>(max) - min + 1);
}

inline constexpr double RNG::int_to_double(std::uint_fast32_t min, std::uint_fast32_t max, std::uint_fast32_t i)
{
	return (i - min) * inv_max(min, max);
}

#endif