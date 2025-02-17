#include "pch.hpp"
#include "AudioManager.hpp"

namespace ATMA
{
    AudioManager::AudioManager() {}

    AudioManager::~AudioManager() {}

    unsigned int AudioManager::createAudioChannel(const unsigned int &l_bufferSize, const unsigned int &l_channelCount, const AudioFrequency &l_freq)
    {
        auto id = m_lastId++;
        m_channels[id] = std::make_shared<AudioChannel>(l_bufferSize, l_channelCount, l_freq);
        return id;
    }

    void AudioManager::deleteAudioChannel(const unsigned int &l_id)
    {
        if(auto itr = m_channels.find(l_id); itr != m_channels.end())
            m_channels.erase(itr);
    }

    std::shared_ptr<AudioChannel> AudioManager::getChannel(const unsigned int &l_id)
    {
        if(auto itr = m_channels.find(l_id); itr != m_channels.end())
            return itr->second;
        return nullptr;
    }
}
