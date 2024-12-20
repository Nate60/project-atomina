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

        static inline void dispatch (const std::optional<const unsigned int> &l_id, const NetworkMessage &l_msg, const std::vector<std::shared_ptr<NetworkMessageListener>> &l_subs)
        {
            for(auto &sub: l_subs)
            {
                sub->notify(l_id, l_msg);
            }
        }

        /**
         * pass the event details to the object to be handled
         * @param l_e event details
         */
        virtual void notify(const std::optional<const unsigned int> &l_id, const NetworkMessage &l_e) = 0;

        /**
         * checks if the object is actively listening
         * @returns is listening for events
         */
        bool isEnabled()
        {
            return m_netEnabled;
        }
    protected:
        bool m_netEnabled = true;
    };

}