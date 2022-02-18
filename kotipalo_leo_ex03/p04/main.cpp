#include <iostream>
#include "vdc.hpp"

int main(int argc, char *argv[]) 
{
	//std::uint_fast32_t seed = 1;
	//if (argc > 1) {
	//	try {
	//		seed = std::stoi(argv[1]);
	//	} catch (std::invalid_argument e) {
	//		std::clog << "Invalid seed given." << std::endl;
	//	}
	//} else {
	//	std::clog << "No seed given." << std::endl;
	//}
	//std::clog << "Using seed " << seed << std::endl;

	std::cout << std::fixed;

	VDC vdc_7(7);
	vdc_7.seed(501);
	std::cout << "Base 7" << std::endl;
	for (int i = 0; i < 10; ++i)
		std::cout << vdc_7.rand() << std::endl;
	std::cout << std::endl;

	std::cout << "Base 11" << std::endl;
	VDC vdc_11(11);
	vdc_11.seed(501);
	for (int i = 0; i < 10; ++i)
		std::cout << vdc_11.rand() << std::endl;
	std::cout << std::endl;

	return 0;
}