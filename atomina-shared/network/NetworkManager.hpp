#pragma once
#include "URL.hpp"
#include "NetworkClient.hpp"
#include "NetworkHost.hpp"
#include "NetworkMessageListener.hpp"
#include "NetworkMessage.hpp"
#include "NetworkSerde.hpp"

namespace ATMA
{

    class NetworkConnection;
    using ConnId = unsigned int;
    using Conn = std::pair<std::shared_ptr<bool>,std::shared_ptr<NetworkConnection>>;
    using ConnMap = std::unordered_map<ConnId, std::shared_ptr<Conn>>;
    using NetworkMessageTypeID = unsigned int;
    using MessageSubscribers = std::unordered_map<
        NetworkMessageTypeID,
        std::vector<std::shared_ptr<NetworkMessageListener>>>;

    class NetworkConnection
    {
    public:
        NetworkConnection(
            const std::optional<const unsigned int> &l_id,
            std::shared_ptr<Socket> &l_conn,
            const std::shared_ptr<bool> &l_connected,
            const std::shared_ptr<MessageSubscribers> &l_subscribers
        ):
            m_id(l_id),
            m_conn(l_conn),
            m_connected(l_connected),
            m_subscribers(l_subscribers)
        {
            m_thread = std::thread{&NetworkConnection::run, this};
        }

        void run();

        inline void send(const NetworkMessage &l_msg)
        {
            std::vector<unsigned char> msg = NetworkSerde::serialize(l_msg);
            m_conn->sendBytes(msg, msg.size());
        }

        ~NetworkConnection()
        {
            ATMA_ENGINE_INFO(
                "joining thread for connection {}", 
                m_id.value_or(std::numeric_limits<unsigned int>::max())
            );
            m_thread.join();
        }
    protected:
        std::shared_ptr<Socket> m_conn;
        const std::shared_ptr<bool> m_connected;
        const std::optional<const unsigned int> m_id;
        const std::shared_ptr<MessageSubscribers> m_subscribers;
        std::thread m_thread;
    };

    class NetworkListener
    {
    public:
        NetworkListener(
            std::shared_ptr<SocketListener> &l_listener,
            const std::shared_ptr<bool> &l_listening,
            std::shared_ptr<std::mutex> &l_idMutex,
            std::shared_ptr<ConnMap> &l_connections,
            std::shared_ptr<ConnId> &l_lastId,
            const std::shared_ptr<MessageSubscribers> &l_subscribers
        ):
            m_listener(l_listener),
            m_listening(l_listening),
            m_idMutex(l_idMutex),
            m_connections(l_connections),
            m_lastId(l_lastId),
            m_subscribers(l_subscribers)
        {
            m_thread = std::thread{&NetworkListener::run, this};
        }

        void run();

        ~NetworkListener()
        {
            m_thread.join();
        }

    protected:
        std::shared_ptr<SocketListener> m_listener;
        const std::shared_ptr<bool> m_listening;
        const std::shared_ptr<MessageSubscribers> m_subscribers;
        std::shared_ptr<std::mutex> m_idMutex;
        std::shared_ptr<ConnMap> m_connections;
        std::shared_ptr<ConnId> m_lastId;

        std::thread m_thread;
    };

    class NetworkManager
    {
    public:
        NetworkManager();

        virtual ~NetworkManager();

        void startHosting(const unsigned int &l_port);

        void broadcastMessage(const NetworkMessage &l_msg);

        void stopHosting();

        void startConnection(const URL &l_url, const unsigned short &l_port);

        void sendMessage(const NetworkMessage &l_msg, const std::optional<const ConnId> &l_id = std::nullopt);

        void stopConnection(const std::optional<const ConnId> &l_id = std::nullopt);

        void addMessageListener(
            const unsigned int &l_type,
            std::shared_ptr<NetworkMessageListener> l_listener
        );

        void purgeListeners();
    protected:
        std::shared_ptr<MessageSubscribers> m_subscribers = std::make_shared<MessageSubscribers>();

        std::shared_ptr<bool> m_connected = std::make_shared<bool>(false);
        std::shared_ptr<Socket> m_connSocket = nullptr;
        std::unique_ptr<NetworkConnection> m_conn = nullptr;

        std::shared_ptr<bool> m_listening = std::make_shared<bool>(false);
        std::shared_ptr<SocketListener> m_listenerSocket = nullptr;
        std::unique_ptr<NetworkListener> m_listener = nullptr;
        std::shared_ptr<std::mutex> m_connIdMutex = std::make_shared<std::mutex>();
        std::shared_ptr<ConnMap> m_connections = std::make_shared<ConnMap>();
        std::shared_ptr<ConnId> m_lastConnId = std::make_shared<ConnId>();
    };
}