#pragma once
#include "pch.hpp"
#include "NetworkMessage.hpp"
#include "util/Props.hpp"

namespace ATMA
{
    /**
    * Helper class for serializing and deserializing network messages
    */
    class NetworkSerde
    {
    public:
        /**
        * converts stream of bytes into a network message
        * @param l_bytes stream of bytes from socket
        * @returns message constructed from byte stream
        */
        static const NetworkMessage deserialize(const std::vector<unsigned char> &l_bytes);

        /**
        * converts Network message into byte stream
        * @param l_message Network Message to convert
        * @returns message as a byte stream
        */
        static const std::vector<unsigned char> serialize(const NetworkMessage &l_message);

    };
}


