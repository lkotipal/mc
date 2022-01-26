#ifndef BUFFON_H
#define BUFFON_H

#include <random>
#include <numbers>

class Buffon {
public:
	Buffon(double l, double d) : l(l), d(d), x_dis(0.0, d/2.0), phi_dis(0.0, std::numbers::pi/2) {}
	double simulate(unsigned int n);
private:
	bool needle_drop();
	double l;
	double d;
	std::uniform_real_distribution<double> x_dis;
	std::uniform_real_distribution<double> phi_dis;
	std::mt19937 rng;
};

#endif