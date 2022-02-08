#include <cassert>
#include <iostream>
#include "qcg.hpp"

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

	QCG qcg(seed);
	std::cout << "QCG: " << qcg.rand() << std::endl;

	qcg.seed(seed);
	std::uint32_t i {0};
	double rand {0.0};
	do { 
		rand = qcg.rand();
		assert(rand >= 0.0 && rand < 1.0);
		++i;
	} while (!qcg.has_seed(seed));
	std::cout << "QCG period length " << i << std::endl;
	
	return 0;
}