#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "event/ObjectEventContext.hpp"

namespace ATMA
{

    /**
     * interface for handling internal engine events
     */
    class ATMA_API ObjectEventListener
    {
    public:
        // default constructor
        ObjectEventListener() {}

        // deconstructor
        ~ObjectEventListener() {}

        /**
         * pass the event details to the object to be handled
         * @param l_e event details
         */
        virtual void notify(const ObjectEventContext &l_e) = 0;

        /**
         * checks if the object is actively listening
         * @returns is listening for events
         */
        bool isEnabled()
        {
            return m_enabled;
        }
    protected:
        bool m_enabled = true;
    };

}