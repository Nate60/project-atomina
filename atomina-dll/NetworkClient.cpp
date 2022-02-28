#include "pch.h"
#include "NetworkClient.h"

namespace ATMA {

	NetworkClient::NetworkClient(const std::string l_addr, const int l_port) : _addr(l_addr), _port(l_port)
	{

	}

	NetworkClient::NetworkClient(const NetworkClient& l_other)
	{
		_addr = l_other._addr;
		_port = l_other._port;
	}

	NetworkClient::~NetworkClient()
	{
		_socket.disconnect();
	}

	bool NetworkClient::connect() 
	{
		auto result = _socket.connect(_addr, _port) == sf::Socket::Done;
		return result;
	}

	void NetworkClient::disconnect() 
	{
		_socket.disconnect();
	}

	void NetworkClient::setBlocking(const bool l_bool)
	{
		_socket.setBlocking(l_bool);
	}
	
	bool NetworkClient::sendBytes(const std::byte* l_bytes, const size_t l_length) 
	{
		return _socket.send(l_bytes, l_length) == sf::Socket::Done;
	}

	bool NetworkClient::receiveBytes(std::byte* l_buffer, const size_t l_maxBufferLength, size_t & l_receivedBytes)
	{
		return _socket.receive(l_buffer, l_maxBufferLength, l_receivedBytes) == sf::Socket::Done;
	}

	NetworkClient& NetworkClient::operator=(const NetworkClient& l_other)
	{
		_socket.disconnect();
		_port = l_other._port;
		_addr = l_other._addr;
		return *this;

	}


}