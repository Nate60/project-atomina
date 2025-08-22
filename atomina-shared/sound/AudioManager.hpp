#pragma once
#include "pch.hpp"
#include "AudioChannel.hpp"

namespace ATMA
{
    class ATMAContext;

    class AudioManager
    {
    public:
        AudioManager();
        virtual ~AudioManager();

        [[nodiscard]] unsigned int createAudioChannel(
            ATMAContext *l_ctx,
            const unsigned int &l_bufferSize = 1024u,
            const unsigned int &l_channelCount = 2u,
            const AudioFrequency &l_freq = AudioFrequency::FREQ_44100
        );

        void deleteAudioChannel(const unsigned int &l_id);

        [[nodiscard]] std::shared_ptr<AudioChannel> getChannel(const unsigned int &l_id);

        void purge();
    private:
        std::unordered_map<unsigned int, std::shared_ptr<AudioChannel>> m_channels{};
        unsigned int m_lastId = 0;
    };

}
