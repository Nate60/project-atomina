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
        // constructor defining message type with default and contents with default
        NetworkMessage(const unsigned int &l_messageType = 0u, const ATMA::Props &l_props = ATMA::Props{}):
            m_type(l_messageType),
            m_values(l_props)
        {
        }

        // deconstructor
        virtual ~NetworkMessage() {}

        // copy constructor
        NetworkMessage(const NetworkMessage &l_other): m_type(l_other.m_type), m_values(l_other.m_values) {}

        // move constructor
        NetworkMessage(NetworkMessage &&l_other) noexcept: m_type(l_other.m_type), m_values(l_other.m_values) {}

        // copy operator
        inline NetworkMessage &operator=(const NetworkMessage &l_other)
        {
            m_type = l_other.m_type;
            m_values = l_other.m_values;
            return *this;
        }

        // move operator
        inline NetworkMessage &operator=(NetworkMessage &&l_other)
        {
            m_type = std::move(l_other.m_type);
            m_values = std::move(l_other.m_values);
            return *this;
        }

        // type member getter
        inline const unsigned int &type() const
        {
            return m_type;
        }

        // values member getter
        inline const Props &values() const
        {
            return m_values;
        }
    protected:
        unsigned int m_type;
        Props m_values;
    };
}
