#ifndef ABSORPTION_SIMULATOR_HPP
#define ABSORPTION_SIMULATOR_HPP
#include "point.hpp"
#include "radiation_simulator.hpp"

class Absorption_simulator : public Radiation_simulator {
	public:
		Absorption_simulator(std::uint_fast32_t seed) : Radiation_simulator(seed) {}
		double simulate(int trajectories);
	private:
		bool walk(Point p);
		static constexpr double mu_t{mu_s + mu_a};
		std::exponential_distribution<double> p_s{mu_t};
};

inline double Absorption_simulator::simulate(int trajectories)
{
	int hits{0};
	for (int i = 0; i < trajectories; ++i)
		if (walk({0.0, 0.0}))
			++hits;
	return static_cast<double>(hits) / trajectories;
}

inline bool Absorption_simulator::walk(Point p)
{
	double s = p_s(rng);
	double theta = p_theta(rng);
	Point new_p = p + Point(s, theta);

	if (new_p.norm() > r) {
		// Wall hit, find intersection point

		// First find the equation of the line y = ax + b
		double a = (new_p[1] - p[1]) / (new_p[0] - p[0]);
		double b = p[1] - a * p[0];

		// x^2 + (ax + b)^2 = r^2
		// (1 + a^2) x^2 + 2ab x + b^2 - r^2 = 0
		double x_intersect_1 = (-2 * a * b + std::sqrt(std::pow(2 * a * b, 2) - 4 * (1 + a*a) * (b*b - r*r)) ) / (2 * (1 + a*a));
		double x_intersect_2 = (-2 * a * b - std::sqrt(std::pow(2 * a * b, 2) - 4 * (1 + a*a) * (b*b - r*r)) ) / (2 * (1 + a*a));
		double x_intersect = (p[0] < x_intersect_1 && x_intersect_1 < new_p[0]) || (p[0] > x_intersect_1 && x_intersect_1 > new_p[0]) ? x_intersect_1 : x_intersect_2;
		double y_intersect = a * x_intersect + b;

		return alpha/2 > std::abs(Point(std::array<double, 2> {x_intersect, y_intersect}).ang());	// Take detector centered on the x-axis
	} else if (u(rng) < 1 - mu_s / mu_t) {
		// Absorption
		return false;
	} else {
		// Still walking
		return walk(new_p);
	}
}

#endif