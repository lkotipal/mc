#ifndef BUFFON_H
#define BUFFON_H

#include <cmath>
#include <memory>
#include <numbers>
#include "../p03/rng.hpp"

class Buffon {
public:
	Buffon(double l, double d, RNG* rng) : l{l}, d{d}, rng{rng} {}
	void seed(std::uint_fast32_t seed);
	double simulate(int n);
private:
	bool needle_drop(); // Simulate single needle drop and return whether it falls on a line
	double l; // Needle length
	double d; // Line distance
	std::unique_ptr<RNG> rng;
};

inline void Buffon::seed(std::uint_fast32_t seed) 
{
	rng->seed(seed);
}

inline bool Buffon::needle_drop()
{
	return rng->rand(0, d/2) < l/2 * cos(rng->rand(0, std::numbers::pi/2));
}

#endif