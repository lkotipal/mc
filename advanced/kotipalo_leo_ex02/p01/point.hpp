#ifndef POINT_HPP
#define POINT_HPP
#include <array>
#include <cmath>

class Point {
	public:
		Point(const std::array<double, 2>& x) : x{x} {}
		Point(const double r, const double phi) : Point(std::array<double, 2> {r * std::cos(phi), r * std::sin(phi)}) {}
		double norm() const;
		double ang() const;
		Point operator-() const;
		double operator[](int idx) const;
	private:
		std::array<double, 2> x;
};

inline double Point::norm() const 
{
	double norm{0.0};
	for (double d : x)
		norm += d * d;
	return std::sqrt(norm);
}

inline double Point::ang() const
{
	return atan2(x[1], x[0]);
}

inline double Point::operator[](int idx) const
{
	return x[idx];
}

inline Point Point::operator-() const
{
	std::array<double, 2> new_x;
	for (int i = 0; i < 2; ++i)
		new_x[i] = -x[i];
	return Point(new_x);
}

inline Point operator+(const Point& p1, const Point& p2)
{
	std::array<double, 2> x;
	for (int i = 0; i < 2; ++i)
		x[i] = p1[i] + p2[i];
	return Point(x);
}

inline Point operator-(const Point& p1, const Point& p2)
{
	return p1 + -p2;
}

#endif