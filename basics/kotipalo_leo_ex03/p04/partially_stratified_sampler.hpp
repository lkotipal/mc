#ifndef PARTIALLY_STRATIFIED_SAMPLER_HPP
#define PARTIALLY_STRATIFIED_SAMPLER_HPP
#include "stratified_sampler.hpp"

class Partially_stratified_sampler : public Stratified_sampler {
	protected:
		double generate(const int i, const int n);
	private:
		static constexpr int bins = 100;
};

inline double Partially_stratified_sampler::generate(int i, int n)
{
	return Stratified_sampler::generate(static_cast<int>(1.0 * i / n * bins), bins);
}

#endif