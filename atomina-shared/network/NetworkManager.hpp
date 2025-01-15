#pragma once
#include "URL.hpp"
#include "Socket.hpp"
#include "SocketListener.hpp"
#include "NetworkMessageListener.hpp"
#include "NetworkMessage.hpp"
#include "NetworkSerde.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    class NetworkConnection;
    using ConnId = unsigned int;
    using Conn = std::pair<std::shared_ptr<bool>, std::shared_ptr<NetworkConnection>>;
    using ConnMap = std::unordered_map<ConnId, std::shared_ptr<Conn>>;
    using NetworkMessageTypeID = unsigned int;
    using MessageSubscribers =
        std::unordered_map<NetworkMessageTypeID, std::vector<std::shared_ptr<NetworkMessageListener>>>;

    /**
     * wrapper class used to contain and manage the socket in a separate thread
     * so it can listen and dispatch messages without blocking the main thread
     */
    class NetworkConnection
    {
    public:
        /**
         * only way to construct a Network Connection, with all its required members
         */
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
            if(m_id.has_value())
            {
                m_thread.detach();
            }
        }

        /**
         * pass network message into socket contained by this connection
         * fire and forget
         * @param l_msg network message to pass through socket
         */
        inline void send(const NetworkMessage &l_msg)
        {
            std::vector<unsigned char> msg = NetworkSerde::serialize(l_msg);
            m_conn->sendBytes(msg, msg.size());
        }

        /**
         * destructor will wait for socket thread to terminate first so will
         * block if the connection is not notified to terminate
         */
        virtual ~NetworkConnection()
        {
            ATMA_ENGINE_TRACE(
                "waiting for termination signal from conn {} ", m_id.value_or(std::numeric_limits<unsigned int>::max())
            );
            m_termSignal.acquire();
            ATMA_ENGINE_TRACE(
                "starting destruction of connection {} ", m_id.value_or(std::numeric_limits<unsigned int>::max())
            );
            if(m_thread.joinable())
            {
                ATMA_ENGINE_INFO(
                    "joining thread for connection {}", m_id.value_or(std::numeric_limits<unsigned int>::max())
                );
                m_thread.join();
            }
        }
    protected:
        void run();

        std::shared_ptr<Socket> m_conn;
        const std::shared_ptr<bool> m_connected;
        const std::optional<const unsigned int> m_id;
        const std::shared_ptr<MessageSubscribers> m_subscribers;
        std::binary_semaphore m_termSignal{0};
        std::thread m_thread;
    };

    /**
     * wrapper class used to contain and manage the socket listener in a separate thread
     * so it can listen and fork off socket threads without blocking main thread
     */
    class NetworkListener
    {
    public:
        /**
         * only way to construct a Network Listener, with all its required members
         */
        NetworkListener(
            std::shared_ptr<SocketListener> &l_listener,
            const std::shared_ptr<bool> &l_listening,
            std::shared_ptr<ConnMap> &l_connections,
            std::shared_ptr<std::atomic<ConnId>> &l_lastId,
            const std::shared_ptr<MessageSubscribers> &l_subscribers
        ):
            m_listener(l_listener),
            m_listening(l_listening),
            m_connections(l_connections),
            m_lastId(l_lastId),
            m_subscribers(l_subscribers)
        {
            m_thread = std::thread{&NetworkListener::run, this};
        }

        // destructor
        virtual ~NetworkListener()
        {
            m_thread.join();
        }
    protected:
        void run();
        std::shared_ptr<SocketListener> m_listener;
        const std::shared_ptr<bool> m_listening;
        const std::shared_ptr<MessageSubscribers> m_subscribers;
        std::shared_ptr<ConnMap> m_connections;
        std::shared_ptr<std::atomic<ConnId>> m_lastId;

        std::thread m_thread;
    };

    /**
     * Manager class for handling network connections using dedicated threads for each socket
     * and each listener, as well as dispatching incoming messages to their subscribers
     */
    class NetworkManager
    {
    public:
        // default constructor
        NetworkManager();

        // default destructor
        virtual ~NetworkManager();

        /**
         * for beginning a port listener for accepting connections
         * @param l_port the port to open
         */
        void startHosting(const unsigned int &l_port);

        /**
         * publish a message on all open ports
         * @param l_msg message to send
         */
        void broadcastMessage(const NetworkMessage &l_msg);

        /**
         * send signal to listening thread to terminate
         */
        void stopHosting();

        /**
         * open socket a new thread to poll for incoming messages
         * @param l_url url to connect to
         * @param l_port port to connect on
         */
        void startConnection(const URL &l_url, const unsigned short &l_port);

        /**
         * send message to specified connection, by default no id is given and will use the direct connection
         * as opposed to any accepted connection
         * @param l_msg message to send
         * @param l_id id of connection to send to, by default is null option
         */
        void sendMessage(const NetworkMessage &l_msg, const std::optional<const ConnId> &l_id = std::nullopt);

        /**
         * send signal to connection to terminate, by default no id is given and will send to
         * direct connection
         * @param l_id connection id to terminate, by default is null option
         */
        void stopConnection(const std::optional<const ConnId> &l_id = std::nullopt);

        /**
         * add subscriber to be notified of specific message type
         * @param l_type type of message to be notified of
         * @param l_listener shared pointer to subscriber
         */
        void addMessageListener(const unsigned int &l_type, std::shared_ptr<NetworkMessageListener> l_listener);

        /**
         * notify all connections to terminate
         */
        void purgeConnections();

        /**
         * remove all subscribers
         */
        void purgeListeners();
    protected:
        std::shared_ptr<MessageSubscribers> m_subscribers = std::make_shared<MessageSubscribers>();

        std::shared_ptr<bool> m_connected = std::make_shared<bool>(false);
        std::shared_ptr<Socket> m_connSocket = nullptr;
        std::unique_ptr<NetworkConnection> m_conn = nullptr;

        std::shared_ptr<bool> m_listening = std::make_shared<bool>(false);
        std::shared_ptr<SocketListener> m_listenerSocket = nullptr;
        std::unique_ptr<NetworkListener> m_listener = nullptr;
        std::shared_ptr<ConnMap> m_connections = std::make_shared<ConnMap>();
        std::shared_ptr<std::atomic<ConnId>> m_lastConnId = std::make_shared<std::atomic<ConnId>>();
    };
}