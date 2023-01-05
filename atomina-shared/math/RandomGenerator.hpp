#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /*
     * templated class for generating single random numbers within a given range,
     * each generation requires a new distribution since the range may differ
     * explicit templates for int, float, and double
     */
    template<class T>
    class ATMA_API RandomGenerator
    {
    private:
        std::random_device m_device;
        std::mt19937 m_engine;
        std::uniform_real_distribution<T> m_distribution;
        std::mutex m_mtx;
    public:
        // default constructor
        RandomGenerator(): m_engine(m_device()) {}

        /**
         * @overload of the function call operator
         * used as a shorthand for calling the generate function
         * @tparam numeric type for which the range and result should be
         * @param l_min minimum value inclusive
         * @param l_max maximum value inclusive 
         * @returns random value in range of the given template type
         */
        T operator()(T l_min, T l_max)
        {
            return generate(l_min, l_max);
        }

        /**
         * generates a random number between the given range inclusive
         * @tparam numeric type for the range and result
         * @param l_min minimum value inclusive
         * @param l_max maximum value inclusive
         * @returns random value in range of the given template type
         */
        T generate(T l_min, T l_max)
        {
            std::lock_guard<std::mutex> l_lock{m_mtx};

            if(l_min > l_max)
                std::swap(l_min, l_max);

            if(l_min != m_distribution.min() || l_max != m_distribution.max())
            {
                m_distribution = std::uniform_real_distribution<T>(l_min, l_max);
            }

            return m_distribution(m_engine);
        }
    };

    // explicit template instantiation for support types
    template class RandomGenerator<float>;
    template class RandomGenerator<double>;

    // explicit template specialization for int since it uses different distribution class
    template<>
    class ATMA_API RandomGenerator<int>
    {
    private:
        std::random_device m_device;
        std::mt19937 m_engine;
        std::uniform_int_distribution<int> m_distribution;
        std::mutex m_mtx;
    public:
        // default constructor
        RandomGenerator(): m_engine(m_device()) {}
        
        /**
         * used as a shorthand for calling the generate function
         * @param l_min minimum value inclusive
         * @param l_max maximum value inclusive 
         * @returns random value in range
         */
        int operator()(int l_min, int l_max);

        /**
         * generates a random number between the given range inclusive
         * @param l_min minimum value inclusive
         * @param l_max maximum value inclusive
         * @returns random value in range
         */
        int generate(int l_min, int l_max);
    };

}
