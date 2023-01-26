#pragma once

#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{
    /**
     * defines all possible states within the shared library
     */
    enum class ATMA_API State
    {
        Empty = 0u,
        Dummy = 1u,
        COUNT
    };

    /**
     * wrapper class for State Enum that allows for implicit
     * coversion to unsigned int
     */
    class ATMA_API StateType
    {
    public:
        // normal constructor
        StateType(const State &l_type): m_type(l_type) {}

        // conversion constructor
        StateType(const unsigned int &l_int): m_type(static_cast<State>(l_int)) {}

        // conversion operator
        operator unsigned int()
        {
            return static_cast<unsigned int>(m_type);
        }
    private:
        const State m_type;
    };

}
