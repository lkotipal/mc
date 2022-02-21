#ifndef SAMPLING_DISTRIBUTION_HPP
#define SAMPLING_DISTRIBUTION_HPP
#include <cmath>
#include <memory>
#include <numbers>
#include "distribution.hpp"

class Sampling_distribution : public Distribution
{
public:
	Sampling_distribution(std::uint_fast32_t seed) : Distribution{seed} {};
	double generate();
private:
	static constexpr double a = 2.0;
	static constexpr double mu = 0.0;
	static constexpr double sigma = 4.0;
	bool has_stored_normal{false};
	double stored_normal;
	double generate_normal();
};

inline double Sampling_distribution::generate()
{
	double x;
	double y;
	do {
		do {
			x = generate_normal();
		} while (x < -10 || x > 10);

		y = a * std::exp(-std::pow((x - mu) / sigma, 2)/2)/(sigma * std::sqrt(2 * std::numbers::pi)) * generate_uniform();
	} while (y > f(x));
	return x;
}

inline double Sampling_distribution::generate_normal()
{
	if (has_stored_normal) {
		has_stored_normal = false;
		return stored_normal;
	} else {
		double x1;
		do {
			x1 = generate_uniform();
		} while (x1 == 0.0);
		double r = std::sqrt(-2 * std::log(x1));

		double x2 = generate_uniform();

		stored_normal = sigma * r * std::cos(2 * std::numbers::pi * x2) + mu;
		return sigma * r * std::sin(2 * std::numbers::pi * x2) + mu;
	}
}

#endif