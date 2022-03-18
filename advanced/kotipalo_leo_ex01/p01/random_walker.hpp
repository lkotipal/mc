#ifndef RANDOM_WALKER_HPP
#define RANDOM_WALKER_HPP
#include <cmath>
#include <random>

class Random_walker {
	public:
		Random_walker(std::uint_fast32_t seed) : rng{seed} {}
		int simulate(int n_steps);
	private:
		void step();
		std::mt19937 rng;
		std::uniform_int_distribution<int> dis{0, 3};
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
	switch (dis(rng)) {
	case 0:
		++x;
		break;
	case 1:
		++y;
		break;
	case 2:
		--x;
		break;
	case 3:
		--y;
		break;
	}
}

#endif