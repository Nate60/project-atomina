#pragma once
#include "pch.h"
#include "api.h"

namespace ATMA {

	class ATMA_API NetworkClient
	{
	public:
		//NetworkClient(const std::string l_addr, const int l_port);

		//NetworkClient(const NetworkClient & l_other);

		//bool connect();

		//void disconnect();

		//void setBlocking(const bool l_bool);

		//bool sendBytes(const char* l_bytes, const size_t l_length);

		//bool receiveBytes(char* l_buffer, const size_t l_maxBufferLength, size_t l_receivedBytes);

	protected:
		std::string _addr;
		int _port;
		sf::TcpSocket _socket;

	};

}