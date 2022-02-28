#include "pch.h"
#include "NetworkHost.h"
#include "AtominaException.h"

namespace ATMA {

	NetworkHost::NetworkHost(const int l_port) : _port(l_port)
	{

	}

	NetworkHost::~NetworkHost()
	{
		_listener.close();
	}

	NetworkHost::NetworkHost(const NetworkHost & l_other)
	{
		_port = l_other._port;
			
	}

	bool NetworkHost::startListening()
	{
		return _listener.listen(_port) == sf::Socket::Done;
	}

	void NetworkHost::stopListening()
	{
		_listener.close();
	}

	void NetworkHost::setListenerBlocking(const bool l_block)
	{
		_listener.setBlocking(l_block);
	}

	NetworkHost::ClientId NetworkHost::acceptConnections()
	{

		//need to create a pointer to new object on heap so that it can live outside the function scope
		// TODO: Check for possible memory leak
		sf::TcpSocket* l_client = new sf::TcpSocket();
		if (_listener.accept(*l_client) != sf::Socket::Error) {
			auto id = _nextId;
			_nextId++;
			_clients[id] = l_client;
			return id;
		}
		else {
			return 0;
		}
	}

	void NetworkHost::closeConnection(ClientId l_client)
	{

		_clients[l_client]->disconnect();
		_clients.erase(l_client);

	}

	void NetworkHost::purgeConnections()
	{	
		for (auto l_client : _clients)
		{
			l_client.second->disconnect();
			delete l_client.second;
		}
		_clients.clear();
		_nextId = 1;
	}

	void NetworkHost::broadcastBytes(const std::byte* l_bytes, const size_t l_length)
	{
		for (auto l_client : _clients)
		{
			l_client.second->send(l_bytes, l_length);
		}
	}

	void NetworkHost::setBlocking(ClientId l_client, const bool l_block)
	{
		_clients[l_client]->setBlocking(l_block);
	}

	bool NetworkHost::sendBytes(ClientId l_client, const std::byte* l_bytes, const size_t l_length)
	{
		return _clients[l_client]->send(l_bytes, l_length) == sf::Socket::Done;
	}

	bool NetworkHost::receiveBytes(ClientId l_client, std::byte* l_buffer, const size_t l_maxBufferLength, size_t & l_receivedBytes)
	{
		return _clients[l_client]->receive(l_buffer, l_maxBufferLength, l_receivedBytes) == sf::Socket::Done;
	}

	NetworkHost& NetworkHost::operator=(const NetworkHost& l_other)
	{
		
		purgeConnections();
		_port = l_other._port;
		_nextId = l_other._nextId;
		for (auto l_client : l_other._clients) {
			_clients[l_client.first] = l_client.second;
		}

		return *this;

	}

}