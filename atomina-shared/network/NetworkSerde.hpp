#pragma once
#include "pch.hpp"
#include "NetworkMessage.hpp"
#include "util/Props.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    /**
     * Helper class for serializing and deserializing network messages
     */
    class NetworkSerde
    {
    public:
        /**
         * converts stream of bytes into a network message and as an input param will tell how much of the byte stream
         * was used, will return empty message with invalid message type if deserialization fails
         * @param l_bytes stream of bytes from socket
         * @param l_amountSize input variable to be set to amount of bytes used
         * @returns message constructed from byte stream
         */
        static const NetworkMessage deserialize(const std::vector<unsigned char> &l_bytes, size_t &l_amountUsed);

        /**
         * converts Network message into byte stream
         * @param l_message Network Message to convert
         * @returns message as a byte stream
         */
        static const std::vector<unsigned char> serialize(const NetworkMessage &l_message);
    };
}
