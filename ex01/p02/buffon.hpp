#ifndef BUFFON_H
#define BUFFON_H

#include <numbers>
#include <random>

class Buffon {
public:
	Buffon(double l, double d) : l{l}, d{d}, x_dis{0.0, d/2.0} {}
	void seed(std::uint_fast32_t seed);
	double simulate(unsigned int n);
private:
	bool needle_drop(); // Simulate single needle drop and return whether it falls on a line
	double l; // Needle length
	double d; // Line distance
	std::uniform_real_distribution<double> x_dis;
	std::uniform_real_distribution<double> phi_dis {0.0, std::numbers::pi/2};
	std::mt19937 rng {1};
};

inline void Buffon::seed(std::uint_fast32_t seed) 
{
	rng.seed(seed);
}

inline bool Buffon::needle_drop()
{
	return this->x_dis(rng) < l/2 * cos(phi_dis(rng));
}

#endif