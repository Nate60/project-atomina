#pragma once
#include "../core/api.hpp"

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
		std::random_device m_device;
		std::mt19937 m_engine;
		std::uniform_real_distribution<T> m_distribution;
		std::mutex m_mtx;
	public:

		//default constructor
		RandomGenerator() : m_engine(m_device()) 
		{}

		//calls the generate function with the given range
		T operator()(T l_min, T l_max)
		{
			return generate(l_min, l_max);
		}


		//generates a random number between the given range inclusive
		T generate(T l_min, T l_max)
		{
			std::lock_guard<std::mutex> l_lock{m_mtx};

			if(l_min > l_max) std::swap(l_min, l_max);

			if(l_min != m_distribution.min() || l_max != m_distribution.max())
			{
				m_distribution = std::uniform_real_distribution<T>(l_min, l_max);
			}

			return m_distribution(m_engine);
		}

	};

	//explicit template instantiation for support types
	template class RandomGenerator<float>;
	template class RandomGenerator<double>;

	//explicit template specialization for int since it uses different distribution class
	template<>
	class ATMA_API RandomGenerator<int>
	{
	private:
		std::random_device m_device;
		std::mt19937 m_engine;
		std::uniform_int_distribution<int> m_distribution;
		std::mutex m_mtx;
	public:
				//default constructor
		RandomGenerator(): m_engine(m_device())
		{}

        //calls the generate function with the given range
		int operator()(int l_min, int l_max);

		//generates a random number between the given range inclusive
		int generate(int l_min, int l_max);
	};

}


