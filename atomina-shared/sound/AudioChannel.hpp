#pragma once
#include "pch.hpp"
#include "AudioWave.hpp"
#include "core/ATMAContext.hpp"

namespace ATMA
{

    enum class AudioFrequency 
    {
        FRFQ_8000 = 8000u,
        FREQ_44100 = 44100u,
    };

    struct AudioChannelState
    {
        std::mutex m_stateLock;
        unsigned int m_channelCount{};
        unsigned int m_chunkIndex{};
        unsigned int m_sampleIndex{};
        float m_volume{1.0f};
        std::queue<unsigned int> m_soundQueue{};
    };


    class AudioChannel
    {
    public:
        AudioChannel(const unsigned int &l_bufferSize = 1024u, const unsigned int &l_channelCount = 2u, const AudioFrequency &l_freq = AudioFrequency::FREQ_44100);
        virtual ~AudioChannel();

        void pushSound(const unsigned int &l_id);

        void playNow(const unsigned int &l_id);

    protected:
        static int bufferAudio(
            void *outputBuffer,
            void *inputBuffer,
            unsigned int nBufferFrames,
            double streamTime,
            RtAudioStreamStatus status,
            void *userData
        );

        
        AudioChannelState *m_state{};
        RtAudio m_dac;
    };
}