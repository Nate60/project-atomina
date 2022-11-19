#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "event/ObjectEventContext.hpp"

namespace ATMA
{

    class ATMA_API ObjectEventListener
    {
    public:
        ObjectEventListener() {}

        ~ObjectEventListener() {}

        virtual void notify(const ObjectEventContext &l_e) = 0;

        bool isEnabled()
        {
            return m_enabled;
        }
    protected:
        bool m_enabled = true;
    };

}