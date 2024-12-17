#pragma once
#include "URL.hpp"
#include "NetworkClient.hpp"
#include "NetworkHost.hpp"
#include "NetworkMessageListener.hpp"
#include "NetworkMessage.hpp"
#include "NetworkSerde.hpp"

namespace ATMA
{
    using NetworkMessageTypeID = unsigned int;
    using MessageListeners = std::unordered_map<NetworkMessageTypeID, std::vector<std::shared_ptr<NetworkMessageListener>>>;

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

        void addMessageListener(const unsigned int &l_type, std::shared_ptr<NetworkMessageListener> l_listener);

        void dispatchMessage(const std::optional<const unsigned int> &l_id, const NetworkMessage &l_msg);

        void purgeListeners();

    protected:
        bool m_listening{false};
        bool m_connected{false};
        std::unique_ptr<std::jthread> m_listeningThread = nullptr;
        std::unique_ptr<std::jthread> m_connectionThread = nullptr;
        std::unordered_map<unsigned int, std::jthread> m_receivingThreads{};
        NetworkHost m_host{};
        NetworkClient m_conn{};
        MessageListeners m_listeners{};

    };
}