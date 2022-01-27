#ifndef RNG_H
#define RNG_H
#include <cstdint>

template <std::uint_fast32_t min, std::uint_fast32_t max>
class RNG {
public:
	virtual void seed(std::uint_fast32_t seed) = 0;
	virtual bool has_seed(std::uint_fast32_t seed) = 0;
	double rand();
private:
	virtual std::uint_fast32_t rand_int() = 0;
	static constexpr double inv_max {1.0 / (max - min)};
};

template <std::uint_fast32_t min, std::uint_fast32_t max>
inline double RNG<min, max>::rand()
{
	return (rand_int() - min) * inv_max;
}

#endif