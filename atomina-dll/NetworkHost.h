#pragma once
#include "pch.h"
#include "api.h"

namespace ATMA {

	class ATMA_API NetworkHost 
	{
		using ClientId = unsigned int;
	public:

		//NetworkHost(const int l_port);

		//NetworkHost(const NetworkHost & l_other);

		//ClientId acceptConnections();

		//void closeConnection(ClientId l_client);

		//void purgeConnections();

		//void setBlocking(ClientId l_client, const bool l_block);

		//void broadcastBytes(const char* l_bytes, const size_t l_length);

		//bool sendBytes(ClientId l_client, const char* l_bytes, const size_t l_length);

		//bool receiveBytes(ClientId l_client, char* l_buffer, const size_t l_maxBufferLength, size_t l_receivedBytes);



	protected:

		int _port;
		sf::TcpListener _listener;
		std::unordered_map<ClientId, sf::TcpSocket*> _clients;
		ClientId _nextId = 1;

	};

}