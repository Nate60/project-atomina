#pragma once
#include "pch.hpp"
#include "NetworkMessageTypes.hpp"
#include "util/Props.hpp"

namespace ATMA
{
    static const size_t NETWORKMESSAGEBUFFERSIZE = sizeof(long long) * 8;

    /**
    * Message structure targeted for sending over sockets as byte streams
    */
    class NetworkMessage
    {
    public:
        const unsigned int m_type;
        const ATMA::Props m_values;

        NetworkMessage(
            const unsigned int &l_messageType = 0u,
            const ATMA::Props &l_props = ATMA::Props{}
        ):
            m_type(l_messageType),
            m_values(l_props)
        {
        }
    };
}




