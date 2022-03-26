#ifndef SCATTERING_SIMULATOR_HPP
#define SCATTERING_SIMULATOR_HPP
#include "../p01/point.hpp"
#include "../p01/radiation_simulator.hpp"

class Scattering_simulator : public Radiation_simulator {
	public:
		Scattering_simulator(std::uint_fast32_t seed) : Radiation_simulator(seed) {}
		double simulate(int trajectories);
	protected:
		std::exponential_distribution<double> p_s{mu_s};
	private:
		virtual double walk(Point p, double w);
};

inline double Scattering_simulator::simulate(int trajectories)
{
	double weight{0.0};
	for (int i = 0; i < trajectories; ++i)
		weight += walk({0.0, 0.0}, 1.0);
	return weight / trajectories;
}

inline double Scattering_simulator::walk(Point p, double w)
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

		w *= std::exp(-mu_a * (Point(std::array<double, 2> {x_intersect, y_intersect}) - p).norm());
		return alpha/2 > std::abs(Point(std::array<double, 2> {x_intersect, y_intersect}).ang()) ? w : 0.0;	// Take detector centered on the x-axis
	} else {
		w *= std::exp(-mu_a * s);
		return walk(new_p, w);
	}
}

#endif