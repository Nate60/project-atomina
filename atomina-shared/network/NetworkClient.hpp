#pragma once
#pragma warning(disable: 26812)
#include "../pch.hpp"
#include "../core/api.hpp"
#include "../util/AtominaException.hpp"

namespace ATMA {

	/*
	* Composed of a single TcpSocket for sending and receving bytes
	*/
	class ATMA_API NetworkClient
	{
	public:
		NetworkClient(const std::string l_addr, const int l_port);

		NetworkClient(const NetworkClient & l_other);

		~NetworkClient();

		/*
		* open connection on Client's port and address
		* 
		*/
		void connect();

		/*
		* close Clients connection
		*/
		void disconnect();

		/*
		* Sets whether or not the socket will block on waiting for a connection
		*/
		void setBlocking(const bool l_bool);

		/*
		*  sends bytes over the socket uses std::array to enforce buffer is correct size 
		*  to avoid buffer underflow
		* 
		*  @param l_bytes: array of bytes to send
		*/
		template<size_t N>
		void sendBytes(const std::array<std::byte, N> l_bytes)
		{
			auto result = m_socket.send(l_bytes.data(), N) == sf::Socket::Done;
			if(!result)
				throw NetworkException("Unable to send bytes to remote address [" + m_addr + ":" + std::to_string(m_port) + "]");
		}

		/*
		* receive bytes from socket. enforces buffer size so that way there is not buffer overflow
		* @param l_buffer: buffer to put bytes into
		* @param l_receivedBytes: length of received buffer
		*/
		template<size_t N>
		void receiveBytes(std::array<std::byte,N> &l_buffer, size_t &l_receivedBytes)
		{
			auto result = m_socket.receive(l_buffer.data(), N, l_receivedBytes) == sf::Socket::Done;
			if(!result)
				throw NetworkException("Unable to receive bytes");
		}

		//copy operator
		NetworkClient& operator=(const NetworkClient& l_other);

	protected:
		sf::TcpSocket m_socket;
		std::string m_addr;
		int m_port;


	};

}