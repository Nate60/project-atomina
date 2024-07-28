#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "SocketListener.hpp"
#include "Socket.hpp"
#include "URL.hpp"
#ifdef _WINDOWS_
#    include "platform/Win/network/SocketListenerWinImpl.hpp"
#elif __linux__
#    include "platform/Linux/network/SocketListenerUnixImpl.hpp"
#endif

namespace ATMA
{

    /*
     * TCP Host with one listener and collection of clients spawned from that
     * one listener
     */
    class NetworkHost
    {
        using ClientId = unsigned int;
        using ClientMap = std::unordered_map<ClientId, std::unique_ptr<Socket>>;
    public:
        // constructor specifying the port to listen on
        NetworkHost(const unsigned short &l_port);

        // move constructor
        NetworkHost(NetworkHost &&l_other) noexcept;

        // deconstructor
        virtual ~NetworkHost();

        /**
         * start up listener to start listening for connections on Host port
         * @return if successful
         */
        bool startListening();

        /*
         * stop listener from listening for connections
         */
        void stopListening();

        /**
         * accept any active connections on the socket and give the id for that connection
         * @return the id of the connection, if no connection was made 0 is returned instead
         */
        std::optional<ClientId> acceptConnections();

        /**
         * close the connection of the given client id
         * @param l_client: id of the client connection
         */
        void closeConnection(const ClientId &l_client);

        /**
         * close and remove all client connections
         */
        void purgeConnections();

        /**
         * sets if the client id's corresponding connection is blocking or not
         * @param l_client: id of the client connection
         * @param l_block: if the connection should block or not
         */
        void setBlocking(const ClientId &l_client, const bool &l_block);

        /**
         * send byte buffer on all active connections
         * @tparam the size of the buffer
         * @param l_bytes: byte buffer to send to all clients
         * @return if all message sends were successful
         */
        template<size_t N>
        bool broadcastBytes(const std::span<char, N> &l_bytes)
        {
            bool b{true};
            for(auto &l_client: m_clients)
            {
                if(!(l_client.second->sendBytes(l_bytes)))
                    b = false;
            }
            return b;
        }

        /**
         * send bytes to corresponding client
         * @tparam size of the buffer
         * @param l_client: cliend id of connection
         * @param l_bytes: byte buffer containing bytes to send
         * @return if successful
         */
        template<size_t N>
        bool sendBytes(const ClientId &l_client, const std::span<char, N> &l_bytes)
        {
            ATMA_ENGINE_INFO("Network Host is sending {0} bytes over port: {1}", N, m_port);
            return m_clients[l_client]->sendBytes(l_bytes);
        }

        /**
         * receive bytes from a client connection
         * @tparam size of the buffer
         * @param l_client: client id corresponding to the connection
         * @param l_buffer: byte buffer to store the bytes into
         * @param l_maxBufferLength: max size the buffer can hold
         * @param l_receivedBytes: the amount of bytes received
         * @return if successful
         */
        template<size_t N>
        bool receiveBytes(
            const ClientId &l_client,
            std::span<char, N> &l_buffer,
            size_t &l_receivedBytes
        )
        {
            if(auto res = m_clients[l_client]->receiveBytes(l_buffer, l_receivedBytes); res)
            {
                ATMA_ENGINE_INFO(
                    "Network Host has received {0} bytes over port: {1}", l_receivedBytes, m_port
                );
                return true;
            }
            else
                return false;
        }

        NetworkHost &operator=(NetworkHost &&l_other);
    protected:
        unsigned short m_port;
        std::unique_ptr<SocketListener> m_listener;
        ClientMap m_clients;
        ClientId m_nextId = 0;
    };

}