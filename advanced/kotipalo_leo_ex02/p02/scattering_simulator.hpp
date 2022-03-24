#ifndef SCATTERING_SIMULATOR_HPP
#define SCATTERING_SIMULATOR_HPP
#include "../p01/radiation_simulator.hpp"

class Scattering_simulator : public Radiation_simulator {
	public:
		Scattering_simulator(std::uint_fast32_t seed) : Radiation_simulator(seed) {}
		double simulate(int trajectories);
	protected:
		std::exponential_distribution<double> p_s{mu_s};
	private:
		virtual double walk(double w, double x, double y, double theta);
};

inline double Scattering_simulator::simulate(int trajectories)
{
	double weight{0.0};
	for (int i = 0; i < trajectories; ++i)
		weight += walk(1.0, 0.0, 0.0, p_theta(rng));
	return weight / trajectories;
}

inline double Scattering_simulator::walk(double w, double x, double y, double theta)
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
		double y_intersect = a * x_intersect + b;

		w *= std::exp(-mu_a * std::sqrt(std::pow(x_intersect - x, 2) + std::pow(y_intersect - y, 2)));
		return std::cos(alpha / 2) < x_intersect ? w : 0.0;	// Take detector centered on the x-axis
	} else {
		w *= std::exp(-mu_a * s);
		return walk(w, new_x, new_y, p_theta(rng));
	}
}

#endif