#include "pch.hpp"
#include "AudioManager.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    AudioManager::AudioManager() {}

    AudioManager::~AudioManager() {}

    unsigned int AudioManager::createAudioChannel(
        const unsigned int &l_bufferSize,
        const unsigned int &l_channelCount,
        const AudioFrequency &l_freq
    )
    {
        auto id = m_lastId++;
        m_channels[id] = AudioChannel::makeAudioChannel(l_bufferSize, l_channelCount, l_freq);
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

    void AudioManager::purge()
    {
        m_channels.clear();
        m_lastId = 0;
    }
} // namespace ATMA
