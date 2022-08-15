#include "pch.hpp"
#include "RandomGenerator.hpp"

namespace ATMA
{

    int RandomGenerator<int>::operator()(int l_min, int l_max)
    {
        return generate(l_min, l_max);
    }

    int RandomGenerator<int>::generate(int l_min, int l_max)
    {
        std::lock_guard<std::mutex> l_lock{m_mtx};

        if(l_min > l_max)
            std::swap(l_min, l_max);

        if(l_min != m_distribution.min() || l_max != m_distribution.max())
        {
            m_distribution = std::uniform_int_distribution<int>(l_min, l_max);
        }

        return m_distribution(m_engine);
    }

}