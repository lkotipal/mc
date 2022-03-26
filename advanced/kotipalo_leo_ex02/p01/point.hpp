#ifndef POINT_HPP
#define POINT_HPP
#include <array>
#include <cmath>

template <int D>
class Point {
	public:
		Point(const std::array<double, D>& x) : x{x} {};
		Point() : Point(std::array<double, D>{}) {};
		Point(const double r, const std::array<double, D - 1>& phi);
		double norm() const;
		Point<D> operator-() const;
		double operator[](int idx) const;
	private:
		std::array<double, D> x;
};

template <int D>
inline Point::Point(const double r, const std::array<double, D - 1>& phi)
{
	std::array<double, D> x{};
	for (int i = 0; i < D; ++i)
	{
		x[i] = r;
		for (int j = 0; j < i; ++j)
			x[i] *= std::sin(phi[j]);
		if (i < D - i)
			x[i] *= std::cos(phi[j]);
	}
	return Point(x);
}

template <int D>
inline double Point<D>::norm() const 
{
	double norm{0.0};
	for (double d : x)
		norm += x * x;
	return norm;
}

template <int D>
inline double Point<D>::operator[](int idx) const
{
	return x[idx];
}

template <int D>
inline Point<D> Point<D>::operator-() const
{
	std::array<double, D> x;
	for (int i = 0; i < D; ++i)
		x[i] = -(*this)[i];
	return Point(x);
}

template <int D>
inline Point<D> operator+(const Point<D>& p1, const Point<D>& p2)
{
	std::array<double, D> x;
	for (int i = 0; i < D; ++i)
		x[i] = p1[i] + p2[i];
	return Point(x);
}

template <int D>
inline Point<D> operator-(const Point<D>& p1, const Point<D>& p2)
{
	return p1 + -p2;
}

#endif