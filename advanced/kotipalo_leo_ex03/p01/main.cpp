#include <cmath>
#include <iostream>
#include "kinetic_mc.hpp"
#include "point.hpp"

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

	constexpr double t_max {1E9};	// 1 us = 1E9 fs
	constexpr int trials {3};

	std::cout << "T\tSurvival ratio\t\tJump ratio" << std::endl;
	for (double T : {500.0, 1500.0, 2500.0}) {
		Kinetic_mc kmc {seed, T};

		double mean_survival{0};
		double m_sq_survival{0};

		double mean_jump_ratio{0};
		double m_sq_jump_ratio{0};

		for (int i = 0; i < trials; ++i) {
			kmc.simulate(t_max);
			double prev_mean_survival = mean_survival;
			double prev_mean_jump_ratio = mean_jump_ratio;

			mean_survival += (kmc.survival_ratio() - prev_mean_survival) / (i + 1);
			m_sq_survival += (kmc.survival_ratio() - prev_mean_survival) * (kmc.survival_ratio() - mean_survival);

			mean_jump_ratio += (kmc.jump_ratio() - prev_mean_jump_ratio) / (i + 1);
			m_sq_jump_ratio += (kmc.jump_ratio() - prev_mean_jump_ratio) * (kmc.jump_ratio() - mean_jump_ratio);
		}
		std::cout << std::defaultfloat << T << std::fixed << "\t" ;
		std::cout << mean_survival << " +- " << std::sqrt(m_sq_survival / (trials - 1)) / sqrt(trials) << "\t";
		std::cout << mean_jump_ratio << " +- " << std::sqrt(m_sq_jump_ratio / (trials - 1)) / sqrt(trials) << std::endl;
	}

	double T {1500.0};
	double r_recombine {10.0};
	std::cout << std::endl << std::defaultfloat << "r_recombine = " << r_recombine << std::fixed << std::endl;

	Kinetic_mc kmc {seed, T, r_recombine};

	double mean_survival{0};
	double m_sq_survival{0};

	for (int i = 0; i < trials; ++i) {
		kmc.simulate(t_max);
		double prev_mean_survival = mean_survival;

		mean_survival += (kmc.survival_ratio() - prev_mean_survival) / (i + 1);
		m_sq_survival += (kmc.survival_ratio() - prev_mean_survival) * (kmc.survival_ratio() - mean_survival);
	}
	std::cout << std::defaultfloat << T << std::fixed << "\t" ;
	std::cout << mean_survival << " +- " << std::sqrt(m_sq_survival / (trials - 1)) / sqrt(trials) << std::endl;

	return 0;
}