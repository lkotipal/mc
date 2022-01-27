#ifndef BUFFON_H
#define BUFFON_H

#include <numbers>
#include <random>

class Buffon {
public:
	Buffon(double l, double d) : l{l}, d{d}, x_dis{0.0, d/2.0}, phi_dis{0.0, std::numbers::pi/2} {}
	void seed (std::uint_fast32_t seed) {rng.seed(seed);}
	double simulate(unsigned int n);
private:
	// Simulate single needle dropped and return whether it falls on a line
	bool needle_drop();
	// Needle length
	double l;
	// Line distance
	double d;
	std::uniform_real_distribution<double> x_dis;
	std::uniform_real_distribution<double> phi_dis;
	std::mt19937 rng;
};

#endif