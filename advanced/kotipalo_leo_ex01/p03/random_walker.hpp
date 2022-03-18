#ifndef RANDOM_WALKER_HPP
#define RANDOM_WALKER_HPP
#include <cassert>
#include <cmath>
#include <random>

class Random_walker {
	public:
		Random_walker(std::uint_fast32_t seed) : rng{seed} {}
		std::int64_t simulate();
	private:
		void step();
		std::mt19937 rng;
		std::uniform_int_distribution<int> dis{0, 3};
		int x;
		int y;
};

inline int64_t Random_walker::simulate()
{
	x = 0;
	y = 0;	
	// Just don't overflow lmao
	std::uint64_t steps{0};
	while (x < 10) {
		step();
		++steps;
		assert(steps > 0);
	}
	return steps;
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