#include "pch.hpp"
#include "NetworkManager.hpp"

namespace ATMA
{
    NetworkManager::NetworkManager()
    {

    }

    NetworkManager::~NetworkManager()
    {

    }

    void NetworkManager::startHosting(const unsigned int &l_port)
    {
        std::jthread listeningThread{
            [this](const unsigned int &l_port){
                this->m_host.startListening(l_port);
                while(this->m_listening){
                    auto id = this->m_host.acceptConnections();

                    std::jthread clientThread{
                        [this](const unsigned int &l_id){
                            size_t recvBytes;
                            this->m_host.setBlocking(l_id, true);
                            unsigned char buf[NETWORKMESSAGEBUFFERSIZE];
                            std::span<unsigned char> bufSpan{buf};
                            do
                            {
                                
                                this->m_host.receiveBytes(l_id, bufSpan, NETWORKMESSAGEBUFFERSIZE, recvBytes);

                            }while(recvBytes == 0);
                        },
                        std::ref(id.value())
                    };

                }
            },
            std::ref(l_port)
        };
    }

    void NetworkManager::stopHosting()
    {
        m_listening = false;
    }

    void NetworkManager::startConnection(const URL &l_url, const unsigned int &l_port)
    {

    }

    void NetworkManager::stopConnection()
    {

    }

    void NetworkManager::addMessageListener(const unsigned int &l_type)
    {

    }

    void NetworkManager::purgeListeners()
    {

    }
    
}