#include "pch.h"
#include "NetworkHost.h"

namespace ATMA {

	//NetworkHost::NetworkHost(const int l_port) : _port(l_port)
	//{
	//	_listener.listen(_port);
	//}

	//NetworkHost::NetworkHost(const NetworkHost & l_other)
	//{
	//	_port = l_other._port;
	//	_listener.listen(_port);
	//}

	//NetworkHost::ClientId NetworkHost::acceptConnections()
	//{
	//	sf::TcpSocket l_client;
	//	if (_listener.accept(l_client) == sf::Socket::Done) {
	//		auto id = _nextId;
	//		_nextId++;
	//		_clients[id] = &l_client;
	//		return id;
	//	}
	//	else {
	//		return 0;
	//	}
	//}

	//void NetworkHost::closeConnection(ClientId l_client)
	//{

	//	_clients[l_client]->disconnect();
	//	_clients.erase(l_client);

	//}

	//void NetworkHost::purgeConnections()
	//{
	//	_clients.clear();
	//}

	//void NetworkHost::broadcastBytes(const char* l_bytes, const size_t l_length)
	//{
	//	for (auto l_client : _clients)
	//	{
	//		l_client.second->send(l_bytes, l_length);
	//	}
	//}

	//void NetworkHost::setBlocking(ClientId l_client, const bool l_block)
	//{
	//	_clients[l_client]->setBlocking(l_block);
	//}

	//bool NetworkHost::sendBytes(ClientId l_client, const char* l_bytes, const size_t l_length)
	//{
	//	return _clients[l_client]->send(l_bytes, l_length) == sf::Socket::Done;
	//}

	//bool NetworkHost::receiveBytes(ClientId l_client, char* l_buffer, const size_t l_maxBufferLength, size_t l_receivedBytes)
	//{
	//	return _clients[l_client]->receive(l_buffer, l_maxBufferLength, l_receivedBytes) == sf::Socket::Done;
	//}

}