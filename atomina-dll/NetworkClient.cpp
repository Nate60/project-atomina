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

	void NetworkClient::connect() 
	{
		auto result = m_socket.connect(m_addr, m_port) == sf::Socket::Done;
		if(!result)
			throw NetworkException("Unable to connect to remote address [" + m_addr + ":" + std::to_string(m_port) + "]" );
	}

	void NetworkClient::disconnect() 
	{
		m_socket.disconnect();
	}

	void NetworkClient::setBlocking(const bool l_bool)
	{
		m_socket.setBlocking(l_bool);
	}
	
	NetworkClient& NetworkClient::operator=(const NetworkClient& l_other)
	{
		m_socket.disconnect();
		m_port = l_other.m_port;
		m_addr = l_other.m_addr;
		return *this;

	}

}