#ifndef TGFSR_H
#define TGFSR_H
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>

class TGFSR {
public:
	TGFSR() {};
	std::uint32_t rand();
private:
	static constexpr std::uint32_t w {31};
	static constexpr std::uint32_t p {13};
	static constexpr std::uint32_t q {2};
	static constexpr std::uint32_t a {0x6B5ECCF6};
	std::uint32_t l {0}; // Step 1.
	std::array<std::uint32_t, p> x {101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113}; // Step 2.
};

inline std::uint_fast32_t TGFSR::rand() 
{
	std::uint32_t out = x[l]; // Step 3.
	x[l] = (x[(l + q) % p] ^ (x[l] >> 1) ^ ((x[l] & 0b1) ? a : 0)) & ~(0b1 << 31);	// Step 4'.
	l = (l + 1) % p; // Step 5.
	return out;
}

#endif