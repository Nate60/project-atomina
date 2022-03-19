#pragma once
#include "pch.h"
#include "api.h"

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
		* @return if the connection is successful
		*/
		bool connect();

		/*
		* close Clients connection
		*/
		void disconnect();

		/*
		* Sets whether or not the socket will block on waiting for a connection
		*/
		void setBlocking(const bool l_bool);

		/*
		*  sends bytes over the socket. length specified must match the length of the byte array
		* 
		*  @param l_bytes: array of bytes to send
		*  @param l_length: size of array
		*  @return if send was successful or not
		*/
		bool sendBytes(const std::byte *l_bytes, const size_t l_length);

		/*
		* receive bytes from socket. max length of buffer much match buffer size
		* @param l_buffer: buffer to put bytes into
		* @param l_maxBufferLength: max size of the buffer
		* @param l_receivedBytes: length of received buffer
		* @return if bytes were received
		*/
		bool receiveBytes(std::byte *l_buffer, const size_t l_maxBufferLength, size_t & l_receivedBytes);

		//copy operator
		NetworkClient& operator=(const NetworkClient& l_other);

	protected:
		sf::TcpSocket m_socket;
		std::string m_addr;
		int m_port;


	};

}