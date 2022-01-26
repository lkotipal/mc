#include <iostream>
#include "lcg.hpp"
#include "pm.hpp"
#include "mt.hpp"

int main() {
	std::cout << "Sizes:" << std::endl;

	LCG lcg;
	lcg.seed(15);
	std::cout << "LCG: " << lcg.rand() << std::endl;;

	PM pm;
	pm.seed(7895);
	std::cout << "Park-Miller: " << pm.rand() << std::endl;

	MT mt;
	mt.seed(431);
	std::cout << "Mersenne twister: " << mt.rand() << std::endl;

	std::cout << std::endl;

	lcg.seed(15);
	std::int_fast32_t i = 0;
	do {
		lcg.rand();
		++i;
	} while (!lcg.has_seed(15));
	std::cout << "LCG period length " << i << std::endl;

	pm.seed(7895);
	i = 0;
	do {
		pm.rand();
		++i;
	} while (!pm.has_seed(7895));
	std::cout << "Park-Miller period length " << i << std::endl;

	mt.seed(431);
	i = 0;
	// The period length is an absurd 2^19937 so this will basically run forever
	do {
		mt.rand();
		++i;
	} while (!mt.has_seed(431));
	std::cout << "Mersenne twister period length " << i << std::endl;
}