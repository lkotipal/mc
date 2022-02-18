#ifndef VDC_HPP
#define VDC_HPP
#include <cstdint>

class VDC {
	public:
		VDC(std::uint_fast32_t base) : base{base} {};
		double rand();
		double rand(double min, double max);
		void seed(int seed);
	private:
		double vdc(std::uint_fast32_t n);
		std::uint_fast32_t base;
		std::uint_fast32_t n {0};
};

inline double VDC::rand() 
{
	++n;
	return vdc(n);
}

inline double VDC::rand(double min, double max)
{
	return (max - min) * rand() + min;
}

// Defined s.t. the next number returned is the nth VDC number
inline void VDC::seed(int seed)
{
	n = seed - 1;
}

#endif