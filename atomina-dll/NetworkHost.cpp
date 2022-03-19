#include "pch.h"
#include "NetworkHost.h"
#include "AtominaException.h"

namespace ATMA {

	NetworkHost::NetworkHost(const int l_port) : m_port(l_port)
	{

	}

	NetworkHost::~NetworkHost()
	{
		m_listener.close();
	}

	NetworkHost::NetworkHost(const NetworkHost & l_other)
	{
		m_port = l_other.m_port;
			
	}

	bool NetworkHost::startListening()
	{
		return m_listener.listen(m_port) == sf::Socket::Done;
	}

	void NetworkHost::stopListening()
	{
		m_listener.close();
	}

	void NetworkHost::setListenerBlocking(const bool l_block)
	{
		m_listener.setBlocking(l_block);
	}

	std::optional<NetworkHost::ClientId> NetworkHost::acceptConnections()
	{

		//need to create a pointer to new object on heap so that it can live outside the function scope
		std::unique_ptr<sf::TcpSocket> l_client{new sf::TcpSocket()};
		if (m_listener.accept(*l_client) != sf::Socket::Error) {
			auto id = m_nextId;
			m_nextId++;
			m_clients[id] = std::move(l_client);
			return id;
		}
		else {
			return std::nullopt;
		}
	}

	void NetworkHost::closeConnection(ClientId l_client)
	{

		m_clients[l_client]->disconnect();
		m_clients.erase(l_client);

	}

	void NetworkHost::purgeConnections()
	{	
		for (auto &l_client : m_clients)
		{
			l_client.second->disconnect();
		}
		m_clients.clear();
		m_nextId = 1;
	}

	bool NetworkHost::broadcastBytes(const std::byte *l_bytes, const size_t l_length)
	{
		bool b{true};
		for (auto &l_client : m_clients)
		{
			if(l_client.second->send(l_bytes, l_length) != sf::Socket::Done)
				b = false;
		}
		return b;
	}

	void NetworkHost::setBlocking(ClientId l_client, const bool l_block)
	{
		m_clients[l_client]->setBlocking(l_block);
	}

	bool NetworkHost::sendBytes(ClientId l_client, const std::byte *l_bytes, const size_t l_length)
	{
		return m_clients[l_client]->send(l_bytes, l_length) == sf::Socket::Done;
	}

	bool NetworkHost::receiveBytes(ClientId l_client, std::byte *l_buffer, const size_t l_maxBufferLength, size_t & l_receivedBytes)
	{
		return m_clients[l_client]->receive(l_buffer, l_maxBufferLength, l_receivedBytes) == sf::Socket::Done;
	}

	NetworkHost& NetworkHost::operator=(NetworkHost&& l_other) noexcept
	{
		
		purgeConnections();
		m_port = l_other.m_port;
		m_nextId = l_other.m_nextId;
		for (auto&& l_client : l_other.m_clients) {
			m_clients[l_client.first] = std::move(l_client.second);
		}

		return *this;

	}

}