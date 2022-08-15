#pragma once
#include "../pch.hpp"
#include "../core/api.hpp"

namespace ATMA {

	/*
	* TCP Host with one listener and collection of clients spawned from that
	* one listener
	*/
	class ATMA_API NetworkHost 
	{
		using ClientId = unsigned int;
		using ClientMap = std::unordered_map<ClientId, std::unique_ptr<sf::TcpSocket>>;
	public:

		NetworkHost(const unsigned short l_port);

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
		* @return if all message sends were successful
		*/
		template <size_t N>
		bool broadcastBytes(const std::array<std::byte,N> l_bytes)
		{
			bool b{true};
			for(auto &l_client : m_clients)
			{
				if(l_client.second->send(l_bytes.data(), N) != sf::Socket::Done)
					b = false;
			}
			return b;
		}


		/*
		* send bytes to corresponding client
		* @param l_client: cliend id of connection
		* @param l_bytes: byte buffer containing bytes to send
		* @return if successful
		*/
		template <size_t N>
		bool sendBytes(ClientId l_client, const std::array<std::byte,N> l_bytes)
		{
			return m_clients[l_client]->send(l_bytes.data(), N) == sf::Socket::Done;
		}


		/*
		* receive bytes from a client connection
		* @param l_client: client id corresponding to the connection
		* @param l_buffer: byte buffer to store the bytes into
		* @param l_maxBufferLength: max size the buffer can hold
		* @param l_receivedBytes: the amount of bytes received
		* @return if successful
		*/
		template <size_t N>
		bool receiveBytes(ClientId l_client, std::array<std::byte,N> &l_buffer, size_t &l_receivedBytes)
		{
			return m_clients[l_client]->receive(l_buffer.data(), N, l_receivedBytes) == sf::Socket::Done;
		}

		//copy operator
		NetworkHost& operator=(NetworkHost&& l_other) noexcept;

	protected:

		unsigned short m_port;
		sf::TcpListener m_listener;
		ClientMap m_clients;
		ClientId m_nextId = 0;

	};

}