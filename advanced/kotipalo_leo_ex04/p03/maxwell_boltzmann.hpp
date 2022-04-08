#ifndef MAXWELL_BOLTZMANN_HPP
#define MAXWELL_BOLTZMANN_HPP
#include <cmath>
#include <limits>
#include <numbers>
#include <random>
#include "../p01/state.hpp"

class Maxwell_Boltzmann {
public:
	Maxwell_Boltzmann(double T, std::uint_fast32_t seed);
	State next_state();
	static constexpr double k_B{8.6173E-5};
	double f(const double E);
	double log_f(const double E);
private:
	static constexpr int N{500};
	static constexpr int n{1000};
	const double T;
	std::mt19937 rng;
	std::uniform_real_distribution<double> u{0.0, 1.0};
	State s_0;
};

inline Maxwell_Boltzmann::Maxwell_Boltzmann(double T, std::uint_fast32_t seed) : T{T}, rng{seed}, s_0{State::random_state(N, n, rng)} {
	for (int i = 0; i < 10'000; ++i)
		next_state();
}

inline State Maxwell_Boltzmann::next_state()
{
	State s = s_0.swap(rng);
	//return f(s.E()) / f(s_0.E()) > u(rng) ? s_0 = s : s_0;
	return log_f(s.E()) - log_f(s_0.E()) > std::log(u(rng)) ? s_0 = s : s_0;
}

inline double Maxwell_Boltzmann::f(const double E)
{
	return E > 0 ? std::exp(-E / (k_B * T)) : 0;
}

inline double Maxwell_Boltzmann::log_f(const double E)
{
	return E > 0 ? -E / (k_B * T) : -std::numeric_limits<double>::infinity();
}

#endif