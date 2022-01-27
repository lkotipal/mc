#include <iostream>
#include "lcg.hpp"
#include "pm.hpp"
#include "mt.hpp"

int main(int argc, char *argv[]) 
{
	std::uint_fast32_t seed = 1;
	if (argc > 1) {
		try {
			seed = std::stoi(argv[1]);
		} catch (std::invalid_argument e) {
			std::clog << "Invalid seed given." << std::endl;
		}
	} else {
		std::clog << "No seed given." << std::endl;
	}
	std::clog << "Using seed " << seed << std::endl;

	LCG lcg(seed);
	std::cout << "LCG: " << lcg.rand() << std::endl;

	PM pm(seed);
	std::cout << "Park-Miller: " << pm.rand() << std::endl;

	MT mt(seed);
	std::cout << "Mersenne twister: " << mt.rand() << std::endl;

	std::cout << std::endl;

	lcg.seed(seed);
	std::uint32_t i = 0;
	do {
		lcg.rand();
		++i;
	} while (!lcg.has_seed(seed));
	std::cout << "LCG period length " << i << std::endl;

	pm.seed(seed);
	i = 0;
	do {
		pm.rand();
		++i;
	} while (!pm.has_seed(seed));
	std::cout << "Park-Miller period length " << i << std::endl;

	mt.seed(seed);
	i = 0;
	// The period length is 2^19937 so we should never reach it
	do {
		mt.rand();
		++i;
	} while (!mt.has_seed(seed) && i < std::numeric_limits<std::uint32_t>::max());
	if (mt.has_seed(seed))
		std::cout << "Mersenne twister period length " << i << std::endl;
	else
		std::cout << "Mersenne twister period longer than the maximum integer value " << i << std::endl;
	
	return 0;
}