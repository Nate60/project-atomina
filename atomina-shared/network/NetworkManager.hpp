#pragma once
#include "URL.hpp"
#include "NetworkClient.hpp"
#include "NetworkHost.hpp"
#include "NetworkMessageListener.hpp"

namespace ATMA
{
    using NetworkMessageTypeID = unsigned int;
    using MessageListeners = std::unordered_map<NetworkMessageTypeID, std::vector<NetworkMessageListener>>;

    class NetworkManager
    {
    public:
        NetworkManager();

        virtual ~NetworkManager();

        void startHosting(const unsigned int &l_port);

        void stopHosting();

        void startConnection(const URL &l_url, const unsigned int &l_port);

        void stopConnection();

        void addMessageListener(const unsigned int &l_type);

        void purgeListeners();

    protected:
        bool m_listening{false};
        NetworkHost m_host{};
        NetworkClient m_conn{};
        MessageListeners m_listeners{};

    };
}