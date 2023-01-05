#pragma once
#include <SFML/Network/IpAddress.hpp>
#pragma warning(disable: 26812)
#include "pch.hpp"
#include "core/api.hpp"
#include "util/AtominaException.hpp"

namespace ATMA
{

    /*
     * Composed of a single TcpSocket for sending and receving bytes
     */
    class ATMA_API NetworkClient
    {
    public:

        //constructor specifying address and port of the host for connection
        NetworkClient(const sf::IpAddress l_addr, const unsigned short l_port);

        //copy constructor
        NetworkClient(const NetworkClient &l_other);

        //deconstructor
        ~NetworkClient();

        /**
         * open connection on Client's port and address
         */
        void connect();

        /**
         * close Clients connection
         */
        void disconnect();

        /**
         * Sets whether or not the socket will block on waiting for a connection
         * @param l_bool toggles blocking
         */
        void setBlocking(const bool l_bool);

        /**
         *  sends bytes over the socket uses std::array to enforce buffer is correct size
         *  to avoid buffer underflow
         *  @tparam size of the buffer
         *  @param l_bytes: array of bytes to send
         */
        template<size_t N>
        void sendBytes(const std::array<std::byte, N> l_bytes)
        {
            auto result = m_socket.send(l_bytes.data(), N) == sf::Socket::Done;
            if(!result)
                throw NetworkException(
                    "Unable to send bytes to remote address [" + m_addr.toString() + ":"
                    + std::to_string(m_port) + "]"
                );
        }

        /**
         * receive bytes from socket. enforces buffer size so that way there is not buffer overflow
         * @tparam Size of the buffer
         * @param l_buffer: buffer to put bytes into
         * @param l_receivedBytes: length of received buffer
         */
        template<size_t N>
        void receiveBytes(std::array<std::byte, N> &l_buffer, size_t &l_receivedBytes)
        {
            auto result = m_socket.receive(l_buffer.data(), N, l_receivedBytes) == sf::Socket::Done;
            if(!result)
                throw NetworkException("Unable to receive bytes");
        }

        // copy operator
        NetworkClient &operator=(const NetworkClient &l_other);
    protected:
        sf::TcpSocket m_socket;
        sf::IpAddress m_addr;
        unsigned short m_port;
    };

}