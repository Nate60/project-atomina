#pragma once
#include "core/api.hpp"

namespace ATMA
{

    using SystemType = unsigned int;

    /**
     * Enumeration of all possible system types
     */
    enum class ATMA_API System
    {
        None = 0u,
        Translator = 1u,
        Controller,
        Renderer,
        TextRenderer,
        COUNT
    };

    /**
     * wrapper class for easy conversion from system enum to
     * unsigned int
     */
    class ATMA_API SysType
    {
    public:
        // constructor with name
        SysType(const System &l_type): m_type(l_type) {}

        // conversion constructor
        SysType(const unsigned int &l_int): m_type(static_cast<System>(l_int)) {}

        // conversion operator
        operator unsigned int()
        {
            return static_cast<unsigned int>(m_type);
        }
    private:
        const System m_type;
    };

}