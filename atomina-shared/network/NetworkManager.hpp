#pragma once
#include "URL.hpp"
#include "NetworkClient.hpp"
#include "NetworkHost.hpp"
#include "NetworkMessageListener.hpp"
#include "NetworkMessage.hpp"
#include "NetworkSerde.hpp"

namespace ATMA
{
    using ClientId = unsigned int;
    using ClientMap = std::shared_ptr<std::unordered_map<ClientId, std::shared_ptr<Socket>>>;
    using NetworkMessageTypeID = unsigned int;
    using MessageListeners = std::shared_ptr<std::unordered_map<
        NetworkMessageTypeID,
        std::vector<std::shared_ptr<NetworkMessageListener>>>>;

    class NetworkConnection
    {
    public:
        NetworkConnection(
            std::shared_ptr<Socket> &l_conn,
            const std::shared_ptr<bool> &l_connected,
            const MessageListeners &l_listeners
        ):
            m_conn(l_conn),
            m_connected(l_connected),
            m_listeners(l_listeners)
        {
            m_thread = std::thread{&NetworkConnection::run, this};
        }

        void run();

        ~NetworkConnection()
        {
            m_thread.join();
        }
    protected:
        std::shared_ptr<Socket> m_conn;
        const std::shared_ptr<bool> m_connected;
        const MessageListeners m_listeners;
        std::thread m_thread;
    };

    class NetworkListener
    {
        NetworkListener(
            std::shared_ptr<SocketListener> &l_listener,
            const std::shared_ptr<bool> &l_listening
        ):
            m_listener(l_listener),
            m_listening(l_listening)
        {
            
        }
    protected:
        std::shared_ptr<SocketListener> m_listener;
        const std::shared_ptr<bool> m_listening;
    };

    class NetworkManager
    {
    public:
        NetworkManager();

        virtual ~NetworkManager();

        void startHosting(const unsigned int &l_port);

        void sendMessageToClient(const unsigned int &l_id, const NetworkMessage &l_msg);

        void broadcastMessage(const NetworkMessage &l_msg);

        void stopHosting();

        void startConnection(const URL &l_url, const unsigned short &l_port);

        void sendMessageToConnection(const NetworkMessage &l_msg);

        void stopConnection();

        void addMessageListener(
            const unsigned int &l_type,
            std::shared_ptr<NetworkMessageListener> l_listener
        );

        void purgeListeners();
    protected:
        MessageListeners m_listeners{};

        std::shared_ptr<bool> m_connected = std::make_shared<bool>(false);
        std::shared_ptr<Socket> m_connSocket;
        std::unique_ptr<NetworkConnection> m_conn = nullptr;

        bool m_listening{false};
        URL m_addr{};
        unsigned short m_hostPort{};
        std::shared_ptr<SocketListener> m_listenerSocket;
        ClientMap m_clients;
        ClientId m_nextId = 0;
    };
}