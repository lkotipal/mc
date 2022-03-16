#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <cmath>
#include <random>

class Sphere {
	public:
		Sphere(std::uint_fast32_t seed) : rng{seed} {};
		double simulate(int d, int n);
	private:
		bool hit_or_miss(int d);
		int dim;
		std::mt19937 rng;
		std::uniform_real_distribution<double> dis{-1.0, 1.0};
};

inline double Sphere::simulate(int d, int n)
{
	int hits = 0;
	for (int i = 0; i < n; ++i)
		if (hit_or_miss(d))
			++hits;
	return static_cast<double>(hits) / n;
}

inline bool Sphere::hit_or_miss(int d)
{
	double r_squared = 0.0;
	for (int i = 0; i < d; ++i)
		r_squared += std::pow(this->dis(this->rng), 2);
	return r_squared <= 1.0;
}

#endif