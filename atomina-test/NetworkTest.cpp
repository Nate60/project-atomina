#include "CppUnitTest.h"
#include <atomina.h>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Network {



	TEST_CLASS(Network_Client)
	{

		TEST_CLASS_INITIALIZE(network_startup)
		{
			ATMA::Log::Init();
		}

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

			l_host.startListening();
			l_client.connect();
			l_client.setBlocking(false);
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
			size_t len = 3;
			std::array<std::byte,3> bytes = { std::byte{ 0x60 }, std::byte{ 0x61 }, std::byte{ 0x62 }};
			l_host.broadcastBytes<3>(bytes);
			std::array<std::byte, 3> msg{};
			size_t receivedBytesLen = 0;
			l_client.receiveBytes<3>(msg, receivedBytesLen);

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
			size_t len = 3;
			std::array<std::byte,3> bytes = { std::byte{ 0x60 }, std::byte{ 0x61 }, std::byte{ 0x62 } };
			l_client.sendBytes<3>(bytes);
			std::array<std::byte, 3> msg{};
			size_t receivedBytesLen = 0;
			l_host.receiveBytes<3>(id, msg, receivedBytesLen);

			Assert::AreEqual(len, receivedBytesLen);
			for(int i = 0; i < len; i++)
				Assert::AreEqual(std::to_integer<int>(msg[i]), std::to_integer<int>(bytes[i]));
		}

		TEST_METHOD(Host_can_recive_from_two_connections)
		{
			ATMA::NetworkClient newClient{ addr, port };
			l_host.startListening();
			l_client.connect();
			newClient.connect();
			l_client.setBlocking(false);
			newClient.setBlocking(false);
			unsigned int firstId = l_host.acceptConnections().value_or(100u);
			unsigned int secondId = l_host.acceptConnections().value_or(100u);
			std::array<std::byte,3> bytes = {std::byte{0x60}, std::byte{0x61}, std::byte{0x62}};
			size_t len = 3;
			std::array<std::byte, 3> msg{};
			size_t receivedBytesLen = 0;
			l_client.sendBytes<3>(bytes);
			l_host.receiveBytes<3>(firstId, msg, receivedBytesLen);

			Assert::AreEqual(len, receivedBytesLen);
			for (int i = 0; i < len; i++)
				Assert::AreEqual(std::to_integer<int>(msg[i]), std::to_integer<int>(bytes[i]));

			std::array<std::byte, 3> msg2{};
			newClient.sendBytes<3>(bytes);
			l_host.receiveBytes<3>(secondId, msg2, receivedBytesLen);

			Assert::AreEqual(len, receivedBytesLen);
			for (int i = 0; i < len; i++)
				Assert::AreEqual(std::to_integer<int>(msg2[i]), std::to_integer<int>(bytes[i]));


		}

		TEST_METHOD(No_connection_throws)
		{
			ATMA::NetworkClient client{"0.0.0.0", port};
			client.setBlocking(false);
			try
			{
				auto func = [&]()
				{
					client.connect();
				};
				Assert::ExpectException<ATMA::NetworkException>(func);
			}
			catch(...)
			{

			}
		}

		TEST_METHOD(partial_buffer_receive)
		{
			l_host.startListening();
			l_client.connect();
			l_client.setBlocking(false);
			unsigned int id = l_host.acceptConnections().value_or(100u);
			l_host.setBlocking(id, true);
			std::array<std::byte,3> bytes = {std::byte{ 0x60 }, std::byte{ 0x61 }, std::byte{ 0x62 }};
			size_t len = 3;
			l_client.sendBytes<3>(bytes);
			std::array<std::byte, 1> msg{};
			size_t receivedBytesLen = 0;
			std::array<std::byte, 3> assembled{};
			l_host.receiveBytes<1>(id, msg, receivedBytesLen);
			Assert::IsTrue(receivedBytesLen == 1);
			assembled[0] = msg[0];
			l_host.receiveBytes<1>(id, msg, receivedBytesLen);
			Assert::IsTrue(receivedBytesLen == 1);
			assembled[1] = msg[0];
			l_host.receiveBytes<1>(id, msg, receivedBytesLen);
			Assert::IsTrue(receivedBytesLen == 1);
			assembled[2] = msg[0];
			for(int i = 0; i < len; i++)
			{
				Assert::IsTrue(bytes[i] == assembled[i]);
			}
		

		}

		TEST_METHOD_CLEANUP(close_connections)
		{
			l_host.stopListening();
			l_client.disconnect();
			l_host.purgeConnections();

		}


	};

}