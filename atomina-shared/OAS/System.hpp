#pragma once
#include "core/api.hpp"

namespace ATMA
{

    using SystemType = unsigned int;

    enum class ATMA_API System
    {
        None = 0u,
        Translator = 1u,
        Renderer,
        Controller,
        Animator,
        GUI,
        COUNT
    };

    class ATMA_API SysType
    {
    public:
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