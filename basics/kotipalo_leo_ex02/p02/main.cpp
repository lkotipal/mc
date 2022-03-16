#include <cassert>
#include <iostream>
#include "tgfsr.hpp"

int main(int argc, char *argv[]) 
{
	int n = 0;
	if (argc > 1) {
		try {
			n = std::stoi(argv[1]);
		} catch (std::invalid_argument e) {
			std::clog << "Invalid N given." << std::endl;
		}
	} else {
		std::clog << "No N given." << std::endl;
	}
	std::clog << "N = " << n << std::endl;

	TGFSR tgfsr;
	
	for (int i = 0; i < n; ++i) {
		std::cout << tgfsr.rand() << std::endl;
	}
	
	return 0;
}