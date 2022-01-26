#include "buffon.hpp"
#include <cmath>

double Buffon::simulate(unsigned int n) 
{
	double p = 0;
	for (int i = 0; i < n; ++i)
		if (needle_drop())
			p += 1.0 / n;
	return (2 * l) / (p * d);
}

bool Buffon::needle_drop()
{
	double x = this->x_dis(rng);
	double phi = this->phi_dis(rng);
	return x < l/2 * cos(phi);
}