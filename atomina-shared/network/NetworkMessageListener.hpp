#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "NetworkMessage.hpp"

namespace ATMA
{

    /**
     * interface for handling internal engine events
     */
    class NetworkMessageListener
    {
    public:
        // default constructor
        NetworkMessageListener() {}

        // deconstructor
        ~NetworkMessageListener() {}

        /**
         * pass the event details to the object to be handled
         * @param l_e event details
         */
        virtual void notify(const NetworkMessage &l_e) = 0;

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