#include "pch.hpp"
#include "NetworkManager.hpp"

namespace ATMA
{

    void NetworkConnection::run()
    {
        ATMA_ENGINE_INFO("Starting connection thread");
        size_t recvBytes;
        size_t totalBytes;
        m_conn->setBlocking(false);
        unsigned char buf[NETWORKMESSAGEBUFFERSIZE];
        std::span<unsigned char> bufSpan{buf};
        std::vector<unsigned char> wholeMessage{};
        unsigned short messageSize;
        do
        {
            m_conn->receiveBytes(bufSpan, ATMA::NETWORKMESSAGEBUFFERSIZE, recvBytes);
            if(recvBytes == 0)
                break;
            totalBytes = recvBytes;
            for(int i = 0; i < recvBytes; i++)
            {
                wholeMessage.emplace_back(bufSpan[i]);
            }
            std::copy(
                bufSpan.begin(),
                bufSpan.begin() + sizeof(unsigned short),
                reinterpret_cast<unsigned char *>(&messageSize)
            );
            while(totalBytes < messageSize)
            {
                m_conn->receiveBytes(bufSpan, ATMA::NETWORKMESSAGEBUFFERSIZE, recvBytes);
                totalBytes += recvBytes;
                for(int i = 0; i < recvBytes; i++)
                {
                    wholeMessage.emplace_back(bufSpan[i]);
                }
            }
            ATMA_ENGINE_INFO("Got Network message of {} bytes", totalBytes);
            NetworkMessage msg = NetworkSerde::deserialize(wholeMessage);
            NetworkMessageListener::dispatch(std::nullopt, msg, m_listeners.at(msg.m_type));
        } while(recvBytes == 0 && m_connected);
        ATMA_ENGINE_INFO("Terminating connection thread");
    }

    NetworkManager::NetworkManager() {}

    NetworkManager::~NetworkManager()
    {
        ATMA_ENGINE_INFO("Shutting down Network Manager");
        m_listening = false;
        *m_connected = false;
        if(m_listenerSocket != nullptr)
        {
            m_listenerSocket->stopListening();
        }
        if(m_conn != nullptr)
        {
            m_conn = nullptr;
        }
        if(m_connSocket != nullptr)
        {
            m_connSocket->closeSocket();
        }
        m_clients.clear();
    }

    void NetworkManager::startHosting(const unsigned int &l_port)
    {
        m_listenerSocket = SocketListener::makeSocketListener(l_port);
        if(m_listening)
        {
            ATMA_ENGINE_WARN("Already listening");
            return;
        }
        m_listening = true;
        m_listenerSocket->startListening();
        ATMA_ENGINE_INFO("Starting listening thread");
        /* auto clientThreadFunc = [this](const unsigned int &l_id, NetworkHost &l_host)
         {
             size_t recvBytes;
             size_t totalBytes;
             l_host.setBlocking(l_id, false);
             unsigned char buf[NETWORKMESSAGEBUFFERSIZE];
             std::span<unsigned char> bufSpan{buf};
             std::vector<unsigned char> wholeMessage{};
             unsigned short messageSize;
             do
             {
                 ATMA_ENGINE_INFO("Spawning client receiving thread");
                 l_host.receiveBytes(l_id, bufSpan, ATMA::NETWORKMESSAGEBUFFERSIZE, recvBytes);
                 if(recvBytes == 0)
                     break;
                 totalBytes = recvBytes;
                 for(int i = 0; i < recvBytes; i++)
                 {
                     wholeMessage.emplace_back(bufSpan[i]);
                 }
                 std::copy(
                     bufSpan.begin(),
                     bufSpan.begin() + sizeof(unsigned short),
                     reinterpret_cast<unsigned char *>(&messageSize)
                 );
                 while(totalBytes < messageSize)
                 {
                     l_host.receiveBytes(
                         l_id, bufSpan, ATMA::NETWORKMESSAGEBUFFERSIZE, recvBytes
                     );
                     totalBytes += recvBytes;
                     for(int i = 0; i < recvBytes; i++)
                     {
                         wholeMessage.emplace_back(bufSpan[i]);
                     }
                 }
                 ATMA_ENGINE_INFO("Got Network message of {} bytes", totalBytes);
                 NetworkMessage msg = NetworkSerde::deserialize(wholeMessage);
                 this->dispatchMessage(std::optional<const unsigned int>{l_id}, msg);
             } while(recvBytes == 0);
             ATMA_ENGINE_INFO("Terminating Client id: {} thread", l_id);
         };
         auto listeningThreadFunc = [this,&clientThreadFunc](const unsigned short &l_port,
         NetworkHost &l_host)
         {
             ATMA_ENGINE_INFO("Starting listening thread");
             this->m_host.startListening(l_port);
             while(this->m_listening)
             {
                 auto id = this->m_host.acceptConnections();
                 std::jthread clientThread{clientThreadFunc, std::ref(id.value()),
         std::ref(l_host)};
             }
             this->m_listening = false;
             ATMA_ENGINE_INFO("Terminating listening thread");
         };
         m_listening = true;
         m_listeningThread = std::make_unique<std::jthread>(std::jthread{
             listeningThreadFunc,
             std::ref(l_port),
             std::ref(m_host)
         });*/
        // m_listening = false;
        // m_listenerSocket->stopListening();
    }

    void NetworkManager::sendMessageToClient(const unsigned int &l_id, const NetworkMessage &l_msg)
    {
        std::vector<unsigned char> msg = NetworkSerde::serialize(l_msg);
        m_clients[l_id]->sendBytes(msg, msg.size());
    }

    void NetworkManager::broadcastMessage(const NetworkMessage &l_msg)
    {
        std::vector<unsigned char> msg = NetworkSerde::serialize(l_msg);
        for(auto &l_client: m_clients)
        {
            l_client.second->sendBytes(msg, msg.size());
        }
    }

    void NetworkManager::stopHosting()
    {
        m_listening = false;
        m_listenerSocket->stopListening();
        m_listenerSocket = nullptr;
    }

    void NetworkManager::startConnection(const URL &l_url, const unsigned short &l_port)
    {
        if(*m_connected)
        {
            ATMA_ENGINE_WARN("Already connected");
            return;
        }
        m_connSocket = Socket::makeSocket();
        m_connSocket->connectSocket(l_url, l_port);
        m_connSocket->setBlocking(true);
        *m_connected = true;
        m_conn = std::make_unique<NetworkConnection>(m_connSocket, m_connected, m_listeners);
    }

    void NetworkManager::sendMessageToConnection(const NetworkMessage &l_msg)
    {
        std::vector<unsigned char> msg = NetworkSerde::serialize(l_msg);
        m_connSocket->sendBytes(msg, msg.size());
    }

    void NetworkManager::stopConnection()
    {
        *m_connected = false;
        m_conn = nullptr;
        m_connSocket->closeSocket();
        m_connSocket = nullptr;
    }

    void NetworkManager::addMessageListener(
        const unsigned int &l_type,
        std::shared_ptr<NetworkMessageListener> l_listener
    )
    {
        auto itr = m_listeners.find(l_type);
        if(itr == m_listeners.end())
        {
            std::vector<std::shared_ptr<NetworkMessageListener>> newVec{l_listener};
            m_listeners[l_type] = newVec;
            ATMA_ENGINE_INFO(
                "Network Event Listener for Network Event Type: {0:d} has been added", l_type
            );
        }
        else
        {
            m_listeners[l_type].emplace_back(l_listener);
            ATMA_ENGINE_INFO(
                "Network Event Listener for Network Event Type: {0:d} has been added", l_type
            );
        }
    }

    void NetworkManager::purgeListeners()
    {
        m_listeners.clear();
    }

}