#ifndef RADIATION_SIMULATOR_HPP
#define RADIATION_SIMULATOR_HPP
#include <cmath>
#include <random>

class Radiation_simulator {
	public:
		Radiation_simulator(std::uint_fast32_t seed) : rng{seed} {}
		virtual double simulate(int trajectories) = 0;
	protected:
		static constexpr double pi{M_PI};
		static constexpr double r{1};
		static constexpr double alpha{2 * pi * 10 / 360};
		static constexpr double mu_s{4.0};
		static constexpr double mu_a{1.0};

		std::mt19937 rng;
		std::uniform_real_distribution<double> p_theta{0, 2 * pi};
		std::uniform_real_distribution<double> u{0, 1};
};

#endif