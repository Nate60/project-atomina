#include "RandomGenerator.h"


namespace ATMA {

	//template instances for the accceptable types. Needed to be exported for visability
	template ATMA_API class RandomGenerator<int>;
	template ATMA_API class RandomGenerator<float>;
	template ATMA_API class RandomGenerator<double>;

	int RandomGenerator<int>::operator()(int l_min, int l_max) {
		return generate(l_min, l_max);
	}

	float RandomGenerator<float>::operator()(float l_min, float l_max) {
		return generate(l_min, l_max);
	}

	double RandomGenerator<double>::operator()(double l_min, double l_max) {
		return generate(l_min, l_max);
	}

	//explicit specialization requries an empty template: C2906
	template <>
	int RandomGenerator<int>::generate(int l_min, int l_max) {
		mtx_.lock();

		if (l_min > l_max) std::swap(l_min, l_max);

		if (l_min != intDistribution_.min() || l_max != intDistribution_.max()) {
			intDistribution_ = std::uniform_int_distribution<int>(l_min, l_max);
		}

		return intDistribution_(engine_);
	}

	
	template <>
	float RandomGenerator<float>::generate(float l_min, float l_max) {
		mtx_.lock();

		if (l_min > l_max) std::swap(l_min, l_max);

		if (l_min != floatDistribution_.min() || l_max != floatDistribution_.max()) {
			floatDistribution_ = std::uniform_real_distribution<float>(l_min, l_max);
		}

		return floatDistribution_(engine_);
	}

	template <>
	double RandomGenerator<double>::generate(double l_min, double l_max) {
		mtx_.lock();

		if (l_min > l_max) std::swap(l_min, l_max);

		if (l_min != doubleDistribution_.min() || l_max != doubleDistribution_.max()) {
			doubleDistribution_ = std::uniform_real_distribution<double>(l_min, l_max);
		}

		return doubleDistribution_(engine_);
	}

}