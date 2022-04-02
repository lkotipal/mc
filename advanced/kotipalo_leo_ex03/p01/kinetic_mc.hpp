#ifndef KINETIC_MC_HPP
#define KINETIC_MC_HPP
#include <cmath>
#include <random>
#include <vector>
#include "point.hpp"

class Kinetic_mc {
	public:
		Kinetic_mc(std::uint_fast32_t seed, double T, double r_recombine) : rng {seed}, T {T}, Gamma_i {w_i * std::exp(-E_i / (k_B * T))}, Gamma_v {w_v * std::exp(-E_v / (k_B * T))}, r_recombine{r_recombine} {initialize();}
		Kinetic_mc(std::uint_fast32_t seed, double T) : Kinetic_mc(seed, T, 4.0) {}
		void simulate(double t_max);
		double survival_ratio() const {return static_cast<double>(interstitials.size()) / initial_defects;}
		double jump_ratio() const {return static_cast<double>(interstitial_jumps) / vacancy_jumps;}
	private:
		void initialize();
		void recombine();
		void transition();

		static constexpr double pi {M_PI};
		static constexpr double k_B {8.617E-5};	// ev/K
		static constexpr double w_i {1.717};	// 1/fs
		static constexpr double E_i {1.37};	// eV
		static constexpr double w_v {0.001282};	// 1/fs
		static constexpr double E_v {0.1};	// eV
		const double r_recombine;		// Å

		static constexpr int initial_defects{150};
		const double Gamma_i;
		const double Gamma_v;

		std::mt19937 rng;
		std::vector<Point> interstitials {};
		std::vector<Point> vacancies {};
		int interstitial_jumps {0};
		int vacancy_jumps {0};
		double t {0}; // fs
		double T;
		std::uniform_real_distribution<double> p_theta {0, 2 * pi};
		std::uniform_real_distribution<double> u {0, 1};
};


inline void Kinetic_mc::simulate(double t_max)
{
	initialize();
	while (t < t_max) {
		transition();
	}
}


inline void Kinetic_mc::initialize()
{
	constexpr double r_v {20.0};
	constexpr double r_i {60.0};

	interstitials.clear();
	vacancies.clear();
	interstitial_jumps = 0;
	vacancy_jumps = 0;
	t = 0;

	std::normal_distribution<double> p_rv {0.0, r_v};
	std::normal_distribution<double> p_ri {0.0, r_i};

	for (int i = 0; i < initial_defects; ++i) {
		interstitials.push_back(p_ri(rng) * random_point(rng));
		vacancies.push_back(p_rv(rng) * random_point(rng));
	}

	recombine();
}

inline void Kinetic_mc::transition()
{
	constexpr double r_jump {2.35};	// Å

	std::uniform_int_distribution<int> p_idx {0, static_cast<int>(interstitials.size())};
	int idx_to_move {p_idx(rng)};
	Point delta = r_jump * random_point(rng);

	// More generally should be weighed based on how many interstitials and vacancies there are but we always have the same amount here
	if (u(rng) < Gamma_i / (Gamma_i + Gamma_v)) {
		interstitials[idx_to_move] = interstitials[idx_to_move] + delta;
		++interstitial_jumps;
	} else {
		vacancies[idx_to_move] = vacancies[idx_to_move] + delta;
		++vacancy_jumps;
	}

	t += -std::log(u(rng)) / (interstitials.size() * Gamma_i + vacancies.size() * Gamma_v);
	recombine();
}

inline void Kinetic_mc::recombine()
{

	auto i = interstitials.begin();
	while (i != interstitials.end()) {
		bool recombine {false};

		auto v = vacancies.begin();
		while (v != vacancies.end()) {
			if ((*i - *v).norm() < r_recombine) {
				v = vacancies.erase(v);
				recombine = true;
				break;
			} else {
				++v;
			}
		}

		if (recombine) {
			i = interstitials.erase(i);
		} else {
			++i;
		}
	}
}

#endif