#include "rng.hpp"

double RNG::rand() {
	// Upcast here to avoid overflow
	return (double) (rand_int() - min()) / ((std::uint_fast64_t) max() - min() + 1);
}