#ifndef POINT_HPP
#define POINT_HPP
#include <array>
#include <cmath>
#include <random>

class Point {
	public:
		Point(const std::array<double, 3>& x) : x{x} {}
		Point(const double r, const double theta, const double phi) : Point(std::array<double, 3> {r * std::sin(theta) * std::cos(phi), r * std::sin(theta) * std::sin(phi), r * std::cos(theta)}) {}
		double norm() const {return std::sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);}
		Point operator-() const {return Point(std::array<double, 3> {-x[0], -x[1], -x[2]});}
		double operator[](int idx) const {return x[idx];}

		template<typename RNG>
		static Point random_point(RNG& rng);
	private:
		std::array<double, 3> x;
		inline static std::normal_distribution<double> dis;
};

inline Point operator+(const Point& p1, const Point& p2)
{
	return Point(std::array<double, 3> {p1[0] + p2[0], p1[1] + p2[1], p1[2] + p2[2]});
}

inline Point operator-(const Point& p1, const Point& p2)
{
	return p1 + -p2;
}

inline Point operator*(const double r, const Point& p)
{
	return Point(std::array<double, 3> {r * p[0], r * p[1], r * p[2]});
}

inline Point operator*(const Point& p, const double r)
{
	return r * p;
}

inline Point operator/(const Point& p, const double r)
{
	return p * (1.0 / r);
}

template<typename RNG>
inline Point Point::random_point(RNG& rng)
{
	//std::uniform_real_distribution<double> x {-1.0, 1.0};
	Point p(std::array<double, 3> {Point::dis(rng), Point::dis(rng), Point::dis(rng)});
	//do {
	//	p = Point(std::array<double, 3> {x(rng), x(rng), x(rng)});
	//} while (p.norm() > 1.0);
	return p / p.norm();
}

#endif