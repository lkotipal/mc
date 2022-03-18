#ifndef RANDOM_WALKER_HPP
#define RANDOM_WALKER_HPP
#include <cmath>
#include <random>

class Random_walker {
	public:
		Random_walker(std::uint_fast32_t seed, int l_1, int l_2) : rng{seed}, l_1{l_1}, l_2{l_2} {}
		int simulate(int n_steps);
	private:
		void step();
		std::mt19937 rng;
		std::uniform_int_distribution<int> dir{0, 3};
		std::uniform_int_distribution<int> len{0, 1};
		const int l_1;
		const int l_2;
		int x;
		int y;
};

inline int Random_walker::simulate(int n_steps)
{
	x = 0;
	y = 0;
	for (int i = 0; i < n_steps; ++i)
		step();
	return x*x + y*y;
}

inline void Random_walker::step()
{
	int delta = len(rng) ? l_1 : l_2;
	switch (dir(rng)) {
	case 0:
		x += delta;
		break;
	case 1:
		y += delta;
		break;
	case 2:
		x -= delta;
		break;
	case 3:
		y -= delta;
		break;
	}
}

#endif