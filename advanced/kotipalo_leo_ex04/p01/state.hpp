#ifndef STATE_HPP
#define STATE_HPP
#include <random>
#include <vector>

class State {
	public:
		State(int n) : v(n, false) {;}
		double E();
		int N();

		template <typename RNG>
		static State random_state(int N, int n, RNG& rng);

		template <typename RNG>
		State swap(RNG& rng);
		bool operator[](int idx);
	private:
		std::vector<bool> v;
};

inline double State::E()
{
	constexpr double E_0 {0.01};
	double E {0.0};
	for (int i = 0; i < v.size(); ++i)
		E += E_0 * v[i] * (i + 1);
	return E;
}

inline int State::N()
{
	int N {0};
	for (bool b : v)
		N += b;
	return N;
}

template <typename RNG>
inline State State::random_state(int N, int n, RNG& rng)
{
	State s {n};
	std::uniform_int_distribution u {0, static_cast<int>(s.v.size() - 1)};
	int i {0};
	while (i < N) {
		int idx {u(rng)};
		if (!s.v[idx]) {
			s.v[idx] = true;
			++i;
		}
	}
	return s;
}

template <typename RNG>
inline State State::swap(RNG& rng)
{
	std::uniform_int_distribution u {0, static_cast<int>(v.size() - 1)};
	int i;
	do {
		i = u(rng);
	} while (!v[i]);

	int j;
	do {
		j = u(rng);
	} while(v[j]);

	State s = *this;
	std::swap(s.v[i], s.v[j]);
	return s;
}

inline bool State::operator[](int idx)
{
	return v[idx];
}

#endif