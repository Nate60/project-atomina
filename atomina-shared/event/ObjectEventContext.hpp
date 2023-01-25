#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Props.hpp"

namespace ATMA
{

    class ATMA_API ObjectEventContext
    {
    public:
        ObjectEventContext(const unsigned int &l_objectEventType, const Props &l_props = Props{});
        ~ObjectEventContext();

        const unsigned int m_objectEventType;
        const Props m_properties{};
    };

}