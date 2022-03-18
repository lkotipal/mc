#ifndef SELF_AVOIDING_WALKER_HPP
#define SELF_AVOIDING_WALKER_HPP
#include <array>
#include <cmath>
#include <random>
#include <set>
#include "point.hpp"

struct Walker_result {
	Walker_result(int r_squared, double weight) : r_squared{r_squared}, weight{weight} {};
	const int r_squared;
	const double weight;
};

class Self_avoiding_walker {
	public:
		Self_avoiding_walker(std::uint_fast32_t seed) : rng{seed} {}
		Walker_result simulate(int n_steps);
	private:
		int step();
		std::mt19937 rng;
		std::uniform_int_distribution<int> dis;
		Point pos;
		std::set<Point> visited_points;
};

inline Walker_result Self_avoiding_walker::simulate(int n_steps)
{
	pos = Point{};
	visited_points.clear();
	double weight{1.0};

	for (int i = 0; i < n_steps; ++i) {
		visited_points.insert(pos);
		if (int moves = step()) {
			if (i)	// First move never alters weight
				weight *= static_cast<double>(moves) / 5;
		} else	{
			// Start over
			return simulate(n_steps);
		}
	}

	return Walker_result(pos.r_squared(), weight);
}

// Return amount of possible moves
inline int Self_avoiding_walker::step()
{
	std::vector<Point> moves;
	for (int dir = 0; dir < 3; ++dir) {
		for (int delta : {-1, 1}) {
			std::array<int, 3> xyz{};
			xyz[dir] += delta;
			Point p = pos + xyz;
			if (!visited_points.contains(p))
				moves.push_back(p);
		}
	}

	if (!moves.empty()) {
		dis = std::uniform_int_distribution<int>(0, moves.size() - 1);
		pos = moves[dis(rng)];
	}

	return moves.size();
}

#endif