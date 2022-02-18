#include "vdc.hpp"

double VDC::vdc(std::uint_fast32_t n)
{
	double result = 0.0;
	double f = 1.0;
	std::uint_fast32_t i {n};
	while (i > 0) {
		f /= base;
		result += f * (i % base);
		i /= base;	// int division for floor
	}
	return result;
}