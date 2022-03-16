#include "buffon.hpp"
#include <cmath>

double Buffon::simulate(int n) 
{
	double p = 0;
	for (int i = 0; i < n; ++i)
		if (needle_drop())
			p += 1.0 / n;
	return (2 * l) / (p * d);
}
