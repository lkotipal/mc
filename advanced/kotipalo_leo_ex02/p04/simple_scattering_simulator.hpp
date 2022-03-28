#ifndef SIMPLE_SCATTERING_SIMULATOR_HPP
#define SIMPLE_SCATTERING_SIMULATOR_HPP
#include "../p02/scattering_simulator.hpp"

class Simple_scattering_simulator : public Scattering_simulator {
	public:
		Simple_scattering_simulator(std::uint_fast32_t seed) : Scattering_simulator(seed) {}
	private:
		double walk(Point p, double w);
};

inline double Simple_scattering_simulator::walk(Point p, double w)
{
	double s = p_s(rng);
	double detector_upper = (Point(r, alpha/2) - p).ang();
	double detector_lower = (Point(r, -alpha/2) - p).ang();
	double detector_angle = detector_upper - detector_lower;
	while (detector_angle < 0)
		detector_angle += 2 * pi;

	bool toward = u(rng) < 0.6;
	std::uniform_real_distribution<double> p_theta;
	if (toward) {
		while (detector_upper < detector_lower)
			detector_upper += 2 * pi;
		w *= detector_angle / (2 * pi) / 0.6;
		p_theta = std::uniform_real_distribution<double>(detector_lower, detector_upper);
	} else {
		while (detector_lower < detector_upper)
			detector_lower += 2 * pi;
		w *= (2 * pi - detector_angle) / (2 * pi) / 0.4;
		p_theta = std::uniform_real_distribution<double>(detector_upper, detector_lower);
	}
	Point new_p = p + Point(s, p_theta(rng));

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