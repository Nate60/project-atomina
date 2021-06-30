#pragma once
#include "api.h"

namespace ATMA {


	/*
	* templated class for generating single random numbers within a given range,
	* each generation requires a new distribution since the range may differ
	* explicit templates for int, float, and double
	*/
	template <class T>
	class ATMA_API RandomGenerator
	{
	private:
		std::random_device device_;
		std::mt19937 engine_;
		std::uniform_int_distribution<int> intDistribution_;
		std::uniform_real_distribution<float> floatDistribution_;
		std::uniform_real_distribution<double> doubleDistribution_;
		std::mutex mtx_;
	public:

		//default constructor
		RandomGenerator() : engine_(device_()) {}

		//calls the generate function with the given range
		T operator()(T l_min, T l_max);

		//generates a random number between the given range inclusive
		T generate(T l_min, T l_max);

	};
}


