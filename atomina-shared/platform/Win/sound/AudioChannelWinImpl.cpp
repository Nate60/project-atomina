#ifdef _WIN32
#    include "pch.hpp"
#    include "AudioChannelWinImpl.hpp"
#    include "resource/ResourceManager.hpp"

namespace ATMA
{

    void HandleRTErr(RtAudioErrorType l_type, const std::string &l_text)
    {
        ATMA_ENGINE_WARN("[RTAUDIO]: {}", l_text);
    }

    AudioChannelWinImpl::AudioChannelWinImpl(
        ATMAContext *ctx,
        const unsigned int &l_bufferSize,
        const unsigned int &l_channelCount,
        const AudioFrequency &l_freq
    ):
        AudioChannel(l_bufferSize, l_channelCount, l_freq)
    {
        ATMA_ENGINE_TRACE("Constructing Audio Channel");
        m_dac.setErrorCallback(&HandleRTErr);
        std::vector<unsigned int> deviceIds = m_dac.getDeviceIds();
        if(deviceIds.size() < 1)
        {
            ATMA_ENGINE_ERROR("no devices found");
            throw ATMA::AtominaException{"no audio devices found"};
        }
        ATMA_ENGINE_TRACE("Got {} devices", deviceIds.size());
        RtAudio::StreamParameters params;
        params.deviceId = m_dac.getDefaultOutputDevice();
        params.nChannels = l_channelCount;
        params.firstChannel = 0;
        unsigned int bufferFrames = l_bufferSize;
        m_state = new RtAudioStreamState{};
        m_state->ctx = ctx;
        m_state->m_channelCount = l_channelCount;
        if(m_dac.openStream(
               &params,
               nullptr,
               RTAUDIO_SINT16,
               static_cast<unsigned int>(l_freq),
               &bufferFrames,
               &AudioChannelWinImpl::bufferAudio,
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

    AudioChannelWinImpl::~AudioChannelWinImpl()
    {
        if(m_dac.isStreamRunning())
            m_dac.closeStream();
    }

    void AudioChannelWinImpl::pushSound(const unsigned int &l_id)
    {
        std::lock_guard<std::mutex> lock{m_state->m_stateLock};
        m_state->m_soundQueue.push(l_id);
    }

    void AudioChannelWinImpl::playNow(const unsigned int &l_id)
    {
        std::lock_guard<std::mutex> lock{m_state->m_stateLock};
        m_state->m_soundQueue = std::queue<unsigned int>{};
        m_state->m_soundQueue.push(l_id);
        m_state->m_chunkIndex = 0;
        m_state->m_sampleIndex = 0;
    }

    int AudioChannelWinImpl::bufferAudio(
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
        RtAudioStreamState *state = (RtAudioStreamState *)userData;
        unsigned int sampleCount = nBufferFrames * state->m_channelCount;
        unsigned short *buffer = (unsigned short *)outputBuffer;
        unsigned int i = 0;
        {
            std::lock_guard<std::mutex> lock{state->m_stateLock};
            if(!state->m_soundQueue.empty())
            {
                auto res = state->ctx->m_resMan->loadResource<ATMA::AudioWave>(state->ctx, state->m_soundQueue.front());

                // Write interleaved audio data.
                unsigned short *data = (unsigned short *)res->m_wave.m_data.data();

                for(; i < sampleCount; ++i)
                {
                    if(state->m_sampleIndex >= res->m_wave.m_data.size() / 2)
                    {
                        if(state->m_soundQueue.size() > 1)
                        {
                            res = state->ctx->m_resMan->loadResource<ATMA::AudioWave>(
                                state->ctx, state->m_soundQueue.front()
                            );
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
#endif
