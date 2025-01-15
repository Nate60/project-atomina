#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Log.hpp"
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
         * helper function to send message to corresponding list of subscribers
         * @param l_id connection id
         * @param l_msg message received to be dispatched
         * @param l_subs list of subscribers to send to
         */
        static inline void dispatch(
            const std::optional<const unsigned int> &l_id,
            const NetworkMessage &l_msg,
            const std::vector<std::shared_ptr<NetworkMessageListener>> &l_subs
        )
        {
            for(auto &sub: l_subs)
            {
                sub->notify(l_id, l_msg);
            }
        }

        /**
         * pass the event details to the object to be handled, note that this will happen on a separate thread
         * so all operations done here so be thread safe
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