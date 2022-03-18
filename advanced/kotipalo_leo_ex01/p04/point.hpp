#ifndef POINT_HPP
#define POINT_HPP
#include <array>

class Point {
	public:
		Point(const int x, const int y, const int z) : x{x}, y{y}, z{z} {}
		Point(const std::array<int, 3>& xyz) : Point(xyz[0], xyz[1], xyz[2]) {}
		Point() : Point(0, 0, 0) {}
		int get_x() const {return x;}
		int get_y() const {return y;}
		int get_z() const {return z;}
		int r_squared() const {return x * x + y * y + z * z;}
		Point add(int dir, int delta) const;
		Point operator-() const {return Point(-x, -y, -z);}
		friend auto operator<=>(const Point, const Point) = default;	// Default three-way comparison for std::set
	private:
		int x;
		int y;
		int z;
};

inline Point operator+(const Point& p1, const Point& p2)
{
	return Point(p1.get_x() + p2.get_x(), p1.get_y() + p2.get_y(), p1.get_z() + p2.get_z());
}

inline Point operator-(const Point& p1, const Point& p2)
{
	return p1 + -p2;
}

#endif