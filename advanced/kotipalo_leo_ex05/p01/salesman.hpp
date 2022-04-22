#ifndef SALESMAN_HPP
#define SALESMAN_HPP
#include <algorithm>
#include <cmath>
#include <random>
#include <vector>
#include "point.hpp"

class Salesman {
    public:
        Salesman(std::vector<Point>& cities);

        template <typename RNG>
        double simulate(RNG& rng);
        std::vector<Point> get_route();
    private:
        template <typename RNG>
        void anneal(RNG& rng, double T);

        double f() const;
        double delta_f(const int i, const int j) const;

        std::uniform_real_distribution<double> u {0, 1};
        std::vector<Point> cities;
        std::vector<int> route;
        double T_0;
};

inline Salesman::Salesman(std::vector<Point>& cities) : cities{cities}, route(cities.size())
{
    for (int i = 0; i < cities.size(); ++i)
        route[i] = i;

    for (int i = 0; i < cities.size(); ++i) { 
        for (int j = i + 1; j < cities.size(); ++j) {
            double dist = 2 * (cities[i] - cities[j]).norm();
            if (dist > T_0)
                T_0 = dist;
        }
    }
}

template <typename RNG>
inline double Salesman::simulate(RNG& rng)
{
    double T {T_0};
    while (T > T_0 * 1E-9) {
        anneal(rng, T);
        T *= (1 - 1E-3);
    }
    return f();
}

inline std::vector<Point> Salesman::get_route()
{
    std::vector<Point> ret;
    for (int i = 0; i < cities.size(); ++i)
        ret.push_back(cities[route[i]]);
    return ret;
}

template <typename RNG>
inline void Salesman::anneal(RNG& rng, double T)
{
    std::uniform_int_distribution<int> idx(0, route.size() - 1);
    int i {idx(rng)};
    int j;
    do {
        j = idx(rng);
    } while (j == i);

    if (u(rng) < std::exp(-delta_f(i, j) / T))
        std::swap(route[i], route[j]);
}

inline double Salesman::f() const
{
    double d {0.0};
    for (int i = 0; i < route.size() - 1; ++i)
        d += (cities[route[i]] - cities[route[i+1]]).norm();
    d += (cities[route[route.size() - 1]] - cities[route[0]]).norm();
    return d;
}

// Extremely cursed
inline double Salesman::delta_f(const int i, const int j) const
{
    int prev_i = i == 0 ? cities.size() - 1 : i - 1;
    int next_i = i == cities.size() - 1 ? 0 : i + 1;

    int prev_j = j == 0 ? cities.size() - 1 : j - 1;
    int next_j = j == cities.size() - 1 ? 0 : j + 1;

    if (i == prev_j)
        return (cities[route[i]] - cities[route[next_j]]).norm() + (cities[route[j]] - cities[route[prev_i]]).norm() -
            (cities[route[i]] - cities[route[prev_i]]).norm() - (cities[route[j]] - cities[route[next_j]]).norm();
    else if (i == next_j)
        return (cities[route[i]] - cities[route[prev_j]]).norm() + (cities[route[j]] - cities[route[next_i]]).norm() -
        (cities[route[i]] - cities[route[next_i]]).norm() - (cities[route[j]] - cities[route[prev_j]]).norm();
    else 
        return (cities[route[i]] - cities[route[prev_j]]).norm() + (cities[route[i]] - cities[route[next_j]]).norm() +
        (cities[route[j]] - cities[route[prev_i]]).norm() + (cities[route[j]] - cities[route[next_i]]).norm() -
        (cities[route[i]] - cities[route[prev_i]]).norm() - (cities[route[i]] - cities[route[next_i]]).norm() -
        (cities[route[j]] - cities[route[prev_j]]).norm() - (cities[route[j]] - cities[route[next_j]]).norm();
}

#endif
