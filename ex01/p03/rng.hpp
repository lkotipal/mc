#ifndef RNG_H
#define RNG_H
#include <cstdint>
#include <random>

class RNG {
public:
	virtual void seed(std::uint_fast32_t seed) = 0;
	virtual bool has_seed(std::uint_fast32_t seed) = 0;
	virtual std::uint_fast32_t min();
	virtual std::uint_fast32_t max();
	double rand();
private:
	virtual std::uint_fast32_t rand_int() = 0;
};

#endif