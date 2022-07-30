#include "../pch.hpp"
#include "NetworkHost.hpp"
#include "../util/AtominaException.hpp"

namespace ATMA {

	NetworkHost::NetworkHost(const unsigned short l_port) : m_port(l_port)
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



	void NetworkHost::setBlocking(ClientId l_client, const bool l_block)
	{
		m_clients[l_client]->setBlocking(l_block);
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