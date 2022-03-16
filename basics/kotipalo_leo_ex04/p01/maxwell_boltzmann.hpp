#ifndef MAXWELL_BOLTZMANN_HPP
#define MAXWELL_BOLTZMANN_HPP
#include <cmath>
#include <numbers>
#include <random>

class Maxwell_Boltzmann {
public:
	Maxwell_Boltzmann(std::uint_fast32_t seed, double delta_max) : rng{seed}, delta_E{-delta_max, delta_max} {};
	double mean(const int N);
	double next_double();
	static constexpr double k_B{8.6173324E-5};
	static constexpr double T{500};
	static constexpr double E_theor{3 * k_B * T / 2};
	static constexpr double n(const double E);
private:
	std::mt19937 rng;
	std::uniform_real_distribution<double> delta_E;
	std::uniform_real_distribution<double> u{0.0, 1.0};
	double E_0{E_theor};
};

inline double Maxwell_Boltzmann::mean(const int N)
{
	double sum = 0;
	for (int i = 0; i < N; ++i)
		sum += next_double();
	return sum / N;
}


inline double Maxwell_Boltzmann::next_double()
{
	double next_E = E_0 + delta_E(rng);
	return n(next_E) / n(E_0) > u(rng) ? E_0 = next_E : E_0;
}

inline constexpr double Maxwell_Boltzmann::n(const double E)
{
	return E > 0 ? 2 / std::sqrt(std::numbers::pi) * std::sqrt(E) / std::pow(k_B * T, 3.0 / 2.0) * std::exp(-E / (k_B * T)) : 0;
}

#endif