#include "CppUnitTest.h"
#include <atomina.h>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Network {



	TEST_CLASS(Network_Client)
	{

		int port = 22112;
		std::string addr = "127.0.0.1";
		ATMA::NetworkHost l_host{ port };
		ATMA::NetworkClient l_client{ addr, port };

		TEST_METHOD_INITIALIZE(create_host_and_client)
		{
			l_host = ATMA::NetworkHost(port);
			l_client = ATMA::NetworkClient(addr, port);
		}

		TEST_METHOD(Client_Can_Connect)
		{
			l_client.setBlocking(false);
			l_client.connect();
			l_host.startListening();
			unsigned int id = l_host.acceptConnections().value_or(100u);
			Assert::AreEqual(id, 0u);
		}

		TEST_METHOD(Client_Can_Receive)
		{
			l_host.startListening();
			l_client.connect();
			l_client.setBlocking(true);
			unsigned int id = l_host.acceptConnections().value_or(100u);
			l_host.setBlocking(id, false);
			std::byte bytes[3] = { std::byte{ 0x60 }, std::byte{ 0x61 }, std::byte{ 0x62 }};
			size_t len = 3;
			l_host.broadcastBytes(bytes, len);
			std::byte msg[3];
			size_t receivedBytesLen = 0;
			l_client.receiveBytes(msg, len, receivedBytesLen);

			Assert::AreEqual(len, receivedBytesLen);
			for (int i = 0; i < len; i++)
				Assert::AreEqual(std::to_integer<int>(msg[i]), std::to_integer<int>(bytes[i]));
		}

		TEST_METHOD(Client_Can_Send)
		{
			l_host.startListening();
			l_client.connect();
			l_client.setBlocking(false);
			unsigned int id = l_host.acceptConnections().value_or(100u);
			l_host.setBlocking(id, true);
			std::byte bytes[3] = { std::byte{ 0x60 }, std::byte{ 0x61 }, std::byte{ 0x62 } };
			size_t len = 3;
			l_client.sendBytes(bytes, len);
			std::byte msg[3];
			size_t receivedBytesLen = 0;
			l_host.receiveBytes(id, msg, len, receivedBytesLen);

			Assert::AreEqual(len, receivedBytesLen);
			for(int i = 0; i < len; i++)
				Assert::AreEqual(std::to_integer<int>(msg[i]), std::to_integer<int>(bytes[i]));
		}

		TEST_METHOD(Host_can_recive_from_two_connections)
		{
			ATMA::NetworkClient newClient{ addr, port };
			l_host.startListening();
			l_client.setBlocking(false);
			newClient.setBlocking(false);
			l_client.connect();
			newClient.connect();
			unsigned int firstId = l_host.acceptConnections().value_or(100u);
			unsigned int secondId = l_host.acceptConnections().value_or(100u);
			std::byte bytes[3] = { std::byte{ 0x60 }, std::byte{ 0x61 }, std::byte{ 0x62 } };
			size_t len = 3;
			std::byte msg[3];
			size_t receivedBytesLen = 0;
			l_client.sendBytes(bytes, len);
			l_host.receiveBytes(firstId, msg, len, receivedBytesLen);

			Assert::AreEqual(len, receivedBytesLen);
			for (int i = 0; i < len; i++)
				Assert::AreEqual(std::to_integer<int>(msg[i]), std::to_integer<int>(bytes[i]));

			std::byte msg2[3];
			newClient.sendBytes(bytes, len);
			l_host.receiveBytes(secondId, msg2, len, receivedBytesLen);

			Assert::AreEqual(len, receivedBytesLen);
			for (int i = 0; i < len; i++)
				Assert::AreEqual(std::to_integer<int>(msg2[i]), std::to_integer<int>(bytes[i]));


		}


		TEST_METHOD_CLEANUP(close_connections)
		{
			l_host.stopListening();
			l_client.disconnect();
			l_host.purgeConnections();

		}


	};

}