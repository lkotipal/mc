#ifndef BETTER_SCATTERING_SIMULATOR_HPP
#define BETTER_SCATTERING_SIMULATOR_HPP
#include "../p02/scattering_simulator.hpp"

class Better_scattering_simulator : public Scattering_simulator {
	public:
		Better_scattering_simulator(std::uint_fast32_t seed) : Scattering_simulator(seed) {}
	private:
		double walk(double w, double x, double y, double theta);
};

inline double Better_scattering_simulator::walk(double w, double x, double y, double theta)
{
	double s = p_s(rng);
	double new_x = x + s * std::cos(theta);
	double new_y = y + s * std::sin(theta);

	if (new_x * new_x + new_y * new_y > r * r) {
		// We unfortunately still need the intersection point for determining the change of w

		// First find the equation of the line y = ax + b
		double a = (new_y - y) / (new_x - x);
		double b = y - a * x;

		// x^2 + (ax + b)^2 = r^2
		// (1 + a^2) x^2 + 2ab x + b^2 - r^2 = 0
		double x_intersect_1 = (-2 * a * b + std::sqrt(std::pow(2 * a * b, 2) - 4 * (1 + a*a) * (b*b - r*r)) ) / (2 * (1 + a*a));
		double x_intersect_2 = (-2 * a * b - std::sqrt(std::pow(2 * a * b, 2) - 4 * (1 + a*a) * (b*b - r*r)) ) / (2 * (1 + a*a));
		double x_intersect = (x < x_intersect_1 && x_intersect_1 < new_x) || (x > x_intersect_1 && x_intersect_1 > new_x) ? x_intersect_1 : x_intersect_2;
		double y_intersect = a * x_intersect + b;

		w *= std::exp(-mu_a * std::sqrt(std::pow(x_intersect - x, 2) + std::pow(y_intersect - y, 2)));
		return w * alpha / (2 * pi);	// Just take 1/36 chance to hit detector here
	} else {
		w *= std::exp(-mu_a * s);
		return walk(w, new_x, new_y, p_theta(rng));
	}
}

#endif