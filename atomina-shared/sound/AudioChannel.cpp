#include "pch.hpp"
#include "AudioChannel.hpp"

namespace ATMA
{
    AudioChannel::AudioChannel(
        const unsigned int &l_bufferSize,
        const unsigned int &l_channelCount,
        const AudioFrequency &l_freq
    )
    {
        std::vector<unsigned int> deviceIds = m_dac.getDeviceIds();
        if(deviceIds.size() < 1)
        {
            ATMA_ENGINE_ERROR("no devices found");
            throw ATMA::AtominaException{"no audio devices found"};
        }

        RtAudio::StreamParameters params;
        params.deviceId = m_dac.getDefaultOutputDevice();
        params.nChannels = l_channelCount;
        params.firstChannel = 0;
        unsigned int bufferFrames = l_bufferSize;
        m_state = new AudioChannelState{};
        m_state->m_channelCount = l_channelCount;
        if(m_dac.openStream(
               &params,
               nullptr,
               RTAUDIO_SINT16,
               static_cast<unsigned int>(l_freq),
               &bufferFrames,
               &AudioChannel::bufferAudio,
               (void *)m_state
           ))
        {
            ATMA_ENGINE_ERROR("failed to open stream");
            throw ATMA::AtominaException{"unable to open audio stream"};
        }
        if(m_dac.startStream())
        {
            ATMA_ENGINE_ERROR("failed to start stream: {}", m_dac.getErrorText());
            throw ATMA::AtominaException{"unable to start stream"};
        }
    }

    AudioChannel::~AudioChannel()
    {
        if(m_dac.isStreamRunning())
            m_dac.closeStream();
        delete m_state;
    }

    void AudioChannel::pushSound(const unsigned int &l_id)
    {
        std::lock_guard<std::mutex> lock{m_state->m_stateLock};
        m_state->m_soundQueue.push(l_id);
    }

    void AudioChannel::playNow(const unsigned int &l_id)
    {
        std::lock_guard<std::mutex> lock{m_state->m_stateLock};
        m_state->m_soundQueue = std::queue<unsigned int>{};
        m_state->m_soundQueue.push(l_id);
        m_state->m_chunkIndex = 0;
        m_state->m_sampleIndex = 0;
    }

    int AudioChannel::bufferAudio(
        void *outputBuffer,
        void *inputBuffer,
        unsigned int nBufferFrames,
        double streamTime,
        RtAudioStreamStatus status,
        void *userData
    )
    {
        if(status)
            ATMA_ENGINE_INFO("Stream underflow detected");
        auto &ctx = ATMA::ATMAContext::getContext();
        AudioChannelState *state = (AudioChannelState *)userData;
        unsigned int sampleCount = nBufferFrames * state->m_channelCount;
        unsigned short *buffer = (unsigned short *)outputBuffer;
        unsigned int i = 0;
        {
            std::lock_guard<std::mutex> lock{state->m_stateLock};
            if(!state->m_soundQueue.empty())
            {
                auto res = ctx.loadResource<ATMA::AudioWave>(state->m_soundQueue.front());

                ATMA_ENGINE_TRACE(
                    "buffer size is {} and wave form size is {} ", sampleCount, res->m_wave.m_data.size()
                );
                // Write interleaved audio data.
                unsigned short *data = (unsigned short *)res->m_wave.m_data.data();

                for(; i < sampleCount; ++i)
                {
                    if(state->m_sampleIndex >= res->m_wave.m_data.size() / 2)
                    {
                        if(state->m_soundQueue.size() > 1)
                        {
                            res = ctx.loadResource<ATMA::AudioWave>(state->m_soundQueue.front());
                            state->m_soundQueue.pop();
                            state->m_sampleIndex = 0;
                            state->m_chunkIndex = 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                    buffer[i] = data[state->m_sampleIndex++];
                }
            }
        }

        for(; i < sampleCount; ++i)
        {

            buffer[i] = 0;
        }
        return 0;
    }
}