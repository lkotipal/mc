#ifndef VDC_HPP
#define VDC_HPP
#include <cstdint>

class VDC {
	public:
		VDC(std::uint_fast32_t base) : base{base} {};
		double rand();
		double rand(double min, double max);
	private:
		double vdc(std::uint_fast32_t n);
		std::uint_fast32_t base;
		std::uint_fast32_t n {1};
};

inline double VDC::rand() 
{
	return vdc(n++);
}

inline double VDC::rand(double min, double max)
{
	return (max - min) * rand() + min;
}

inline double VDC::vdc(std::uint_fast32_t n)
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

#endif