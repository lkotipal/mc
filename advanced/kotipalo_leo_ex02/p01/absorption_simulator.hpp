#ifndef ABSORPTION_SIMULATOR_HPP
#define ABSORPTION_SIMULATOR_HPP
#include "radiation_simulator.hpp"

class Absorption_simulator : public Radiation_simulator {
	public:
		Absorption_simulator(std::uint_fast32_t seed) : Radiation_simulator(seed) {}
		double simulate(int trajectories);
	private:
		bool walk(double x, double y, double theta);
		static constexpr double mu_t{mu_s + mu_a};
		std::exponential_distribution<double> p_s{mu_t};
};

inline double Absorption_simulator::simulate(int trajectories)
{
	int hits{0};
	for (int i = 0; i < trajectories; ++i)
		if (walk(0.0, 0.0, p_theta(rng)))
			++hits;
	return static_cast<double>(hits) / trajectories;
}

inline bool Absorption_simulator::walk(double x, double y, double theta)
{
	double s = p_s(rng);
	double new_x = x + s * std::cos(theta);
	double new_y = y + s * std::sin(theta);

	if (new_x * new_x + new_y * new_y > r * r) {
		// Wall hit, find intersection point

		// First find the equation of the line y = ax + b
		double a = (new_y - y) / (new_x - x);
		double b = y - a * x;

		// x^2 + (ax + b)^2 = r^2
		// (1 + a^2) x^2 + 2ab x + b^2 - r^2 = 0
		double x_intersect_1 = (-2 * a * b + std::sqrt(std::pow(2 * a * b, 2) - 4 * (1 + a*a) * (b*b - r*r)) ) / (2 * (1 + a*a));
		double x_intersect_2 = (-2 * a * b - std::sqrt(std::pow(2 * a * b, 2) - 4 * (1 + a*a) * (b*b - r*r)) ) / (2 * (1 + a*a));
		double x_intersect = (x < x_intersect_1 && x_intersect_1 < new_x) || (x > x_intersect_1 && x_intersect_1 > new_x) ? x_intersect_1 : x_intersect_2;
		return std::cos(alpha / 2) < x_intersect;	// Take detector centered on the x-axis
	} else if (u(rng) < 1 - mu_s / mu_t) {
		// Absorption
		return false;
	} else {
		// Still walking
		return walk(new_x, new_y, p_theta(rng));
	}
}

#endif