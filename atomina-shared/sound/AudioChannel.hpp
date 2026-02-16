#pragma once
#include "pch.hpp"

namespace ATMA
{

    class ATMAContext;
    enum class AudioFrequency
    {
        FRFQ_8000 = 8000u,
        FREQ_44100 = 44100u,
    };

    class AudioChannel
    {
    public:
        virtual ~AudioChannel();

        virtual void pushSound(const unsigned int &l_id);

        virtual void playNow(const unsigned int &l_id);

        static std::shared_ptr<AudioChannel> makeAudioChannel(
            ATMAContext *l_ctx,
            const unsigned int &l_bufferSize = 1024u,
            const unsigned int &l_channelCount = 2u,
            const AudioFrequency &l_freq = AudioFrequency::FREQ_44100
        );
        const unsigned int m_bufferSize;
        const unsigned int m_channelCount;
        const AudioFrequency m_freq;
    protected:
        AudioChannel(
            const unsigned int &l_bufferSize = 1024u,
            const unsigned int &l_channelCount = 2u,
            const AudioFrequency &l_freq = AudioFrequency::FREQ_44100
        );
    };
}
