#pragma once
#include "pch.h"
#include "api.h"

namespace ATMA {

	/*
	* TCP Host with one listener and collection of clients spawned from that
	* one listener
	*/
	class ATMA_API NetworkHost 
	{
		using ClientId = unsigned int;
	public:

		NetworkHost(const int l_port);

		NetworkHost(const NetworkHost & l_other);

		~NetworkHost();


		/*
		* start up listener to start listening for connections on Host port
		* @return if successful
		*/
		bool startListening();
		
		/*
		* stop listener from listening for connections
		*/
		void stopListening();

		/*
		* set if listenering should block waiting for connections
		*/
		void setListenerBlocking(const bool l_block);

		/*
		* accept any active connections on the socket and give the id for that connection
		* @return the id of the connection, if no connection was made 0 is returned instead
		*/
		std::optional<ClientId> acceptConnections();

		/*
		* close the connection of the given client id
		* @param l_client: id of the client connection
		*/
		void closeConnection(ClientId l_client);


		/*
		* close and remove all client connections
		*/
		void purgeConnections();

		/*
		* sets if the client id's corresponding connection is blocking or not
		* @param l_client: id of the client connection
		* @param l_block: if the connection should block or not
		*/
		void setBlocking(ClientId l_client, const bool l_block);

		/*
		* send byte buffer on all active connections
		* @param l_bytes: byte buffer to send to all clients
		* @param l_length: length of the buffert to send to all clients
		*/
		void broadcastBytes(const std::byte* l_bytes, const size_t l_length);


		/*
		* send bytes to corresponding client
		* @param l_client: cliend id of connection
		* @param l_bytes: byte buffer containing bytes to send
		* @param l_length: length of byte buffer 
		* @return if successful
		*/
		bool sendBytes(ClientId l_client, const std::byte* l_bytes, const size_t l_length);


		/*
		* receive bytes from a client connection
		* @param l_client: client id corresponding to the connection
		* @param l_buffer: byte buffer to store the bytes into
		* @param l_maxBufferLength: max size the buffer can hold
		* @param l_receivedBytes: the amount of bytes received
		* @return if successful
		*/
		bool receiveBytes(ClientId l_client, std::byte* l_buffer, const size_t l_maxBufferLength, size_t & l_receivedBytes);

		//copy operator
		NetworkHost& operator=(const NetworkHost& l_other);

	protected:

		int m_port;
		sf::TcpListener m_listener;
		std::unordered_map<ClientId, sf::TcpSocket*> m_clients;
		ClientId m_nextId = 0;

	};

}