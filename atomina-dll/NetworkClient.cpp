#include "pch.h"
#include "NetworkClient.h"

namespace ATMA {

	NetworkClient::NetworkClient(const std::string l_addr, const int l_port) : m_addr(l_addr), m_port(l_port)
	{

	}

	NetworkClient::NetworkClient(const NetworkClient& l_other)
	{
		m_addr = l_other.m_addr;
		m_port = l_other.m_port;
	}

	NetworkClient::~NetworkClient()
	{
		m_socket.disconnect();
	}

	bool NetworkClient::connect() 
	{
		auto result = m_socket.connect(m_addr, m_port) == sf::Socket::Done;
		return result;
	}

	void NetworkClient::disconnect() 
	{
		m_socket.disconnect();
	}

	void NetworkClient::setBlocking(const bool l_bool)
	{
		m_socket.setBlocking(l_bool);
	}
	
	bool NetworkClient::sendBytes(const std::byte *l_bytes, const size_t l_length) 
	{
		return m_socket.send(l_bytes, l_length) == sf::Socket::Done;
	}

	bool NetworkClient::receiveBytes(std::byte *l_buffer, const size_t l_maxBufferLength, size_t & l_receivedBytes)
	{
		return m_socket.receive(l_buffer, l_maxBufferLength, l_receivedBytes) == sf::Socket::Done;
	}

	NetworkClient& NetworkClient::operator=(const NetworkClient& l_other)
	{
		m_socket.disconnect();
		m_port = l_other.m_port;
		m_addr = l_other.m_addr;
		return *this;

	}


}