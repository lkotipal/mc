#include <iostream>
#include <iomanip>
#include "vdc.hpp"
#include "direct_sampler.hpp"
#include "stratified_sampler.hpp"
#include "rejection_sampler.hpp"
#include "partially_stratified_sampler.hpp"
#include "importance_sampler.hpp"

inline constexpr double delta_i(const double i)
{
	constexpr double i_exact{0.947019421085};
	return std::abs(i - i_exact);
}

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

	constexpr int start = 501;
	VDC vdc_7(7);
	VDC vdc_11(11);
	for (int i = 0; i < 500; ++i) {
		vdc_7.rand();
		vdc_11.rand();
	}
		
	std::cout << "N\tBase 7\tBase 11" << std::endl;
	for (int i = 0; i < 10; ++i)
		std::cout << std::fixed << std::setprecision(5) << start + i << "\t" << vdc_7.rand() << "\t" << vdc_11.rand() << std::endl;
	std::cout << std::endl;

	std::array<std::unique_ptr<Poisson_integrator>, 5> integrators{
		std::make_unique<Direct_sampler>(),
		std::make_unique<Stratified_sampler>(),
		std::make_unique<Rejection_sampler>(),
		std::make_unique<Partially_stratified_sampler>(),
		std::make_unique<Importance_sampler>()
	};
	std::array<std::string, 5> names{"DS", "SS", "HM", "PSS", "IS"};

	// Header
	std::cout << "\t";
	for (auto name : names)
		std::cout << name << "\t\t";
	std::cout << std::endl;
	std::cout << "N\t";
	for (int i = 0; i < 5; ++i)
		std::cout << "D_I\tt\t";
	std::cout << std::endl;

	// Data
	for (int n = 100; n <= 1'000'000; n *= 10){
		std::cout << std::setw(7) << n << "\t";
		for (int i = 0; i < 5; ++i) {
			auto start = std::clock();
			double result = integrators[i]->integrate(n);
			auto stop = std::clock();
			double time = static_cast<double>(stop - start) / CLOCKS_PER_SEC * 1000;
			std::cout << std::scientific << std::setprecision(1) << delta_i(result) << "\t" << std::defaultfloat << std::setprecision(6) << std::setw(3) << time << " ms\t";
		}
		std::cout << std::endl;
	}

	return 0;
}