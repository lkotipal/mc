#include <cmath>
#include <fstream>
#include <iostream>
#include "point.hpp"
#include "salesman.hpp"

int main(int argc, char *argv[]) 
{
	std::uint_fast32_t seed = 1;
	if (argc > 1) {
		try {
			seed = std::stoi(argv[1]);
		} catch (std::invalid_argument e) {
			std::clog << "Invalid seed given." << std::endl;
		}
	} else {
		std::clog << "No seed given." << std::endl;
	}
	std::clog << "Using seed " << seed << std::endl;

	std::mt19937 rng {seed};
	std::uniform_real_distribution<double> u {0, 1};
	std::uniform_real_distribution<double> theta {0, 2 * M_PI};
	constexpr int trials {100};

	std::vector<Point> square_points;
	for (int i = 0; i < 20; ++i)
		square_points.push_back(Point(std::array<double, 2>{u(rng), u(rng)}));

	std::vector<Point> circle_points;
	for(int i = 0; i < 20; ++i)
		circle_points.push_back(Point(1, theta(rng)));

	std::vector<Point> cities;
	std::ifstream f {"20cities.dat"};
	while (!f.eof()) {
		double x, y;
		std::string name;
		f >> x >> y >> name;
		cities.push_back(Point(std::array<double, 2>{x, y}));
	}
	f.close();

	std::array<std::vector<Point>, 3> point_vecs {square_points, circle_points, cities}; 
	std::array<std::string, 3> names {"square", "circle", "cities"};
	
	for (int i = 0; i < 3; ++i) {
		Salesman sm {point_vecs[i]};
		std::ofstream f_lengths {names[i] + "_lengths.tsv"};
		double min_length = std::numeric_limits<double>::max();
		std::vector<Point> best_route;
		for (int i = 0; i < trials; ++i) {
			double l = sm.simulate(rng);
			f_lengths << std::fixed << l << std::endl;
			if (l < min_length) {
				min_length = l;
				best_route = sm.get_route();
			}
		}
		f_lengths.close();

		std::ofstream f_route {names[i] + "_route.tsv"};
		for (Point p : best_route)
			f_route << std::fixed << p[0] << "\t" << p[1] << std::endl;
	}

	return 0;
}