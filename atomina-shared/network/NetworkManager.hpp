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
    using ClientMap = std::unordered_map<ClientId, std::unique_ptr<Socket>>;
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
        bool m_connected{false};
        bool m_listening{false};
        std::shared_ptr<Socket> m_connSocket;
        URL m_addr{};
        unsigned short m_hostPort{};
        std::shared_ptr<SocketListener> m_listenerSocket;
        ClientMap m_clients;
        ClientId m_nextId = 0;
        MessageListeners m_listeners{};
    };
}