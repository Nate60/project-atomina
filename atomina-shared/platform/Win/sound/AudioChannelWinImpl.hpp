#ifdef _WIN32
#    include "pch.hpp"
#    include "sound/AudioChannel.hpp"
#    include "util/Log.hpp"
#    include "sound/AudioWave.hpp"
#    include "core/ATMAContext.hpp"

namespace ATMA
{

    struct RtAudioStreamState
    {
        ATMAContext *ctx = nullptr;
        std::mutex m_stateLock;
        unsigned int m_channelCount{};
        unsigned int m_chunkIndex{};
        unsigned int m_sampleIndex{};
        float m_volume{1.0f};
        std::queue<unsigned int> m_soundQueue{};
    };

    class AudioChannelWinImpl: public AudioChannel
    {
    public:
        AudioChannelWinImpl(
            ATMAContext *l_ctx,
            const unsigned int &l_bufferSize = 1024u,
            const unsigned int &l_channelCount = 2u,
            const AudioFrequency &l_freq = AudioFrequency::FREQ_44100
        );

        virtual ~AudioChannelWinImpl();

        virtual void pushSound(const unsigned int &l_id);

        virtual void playNow(const unsigned int &l_id);

        static int bufferAudio(
            void *outputBuffer,
            void *inputBuffer,
            unsigned int nBufferFrames,
            double streamTime,
            RtAudioStreamStatus status,
            void *userData
        );
    protected:
        RtAudio m_dac;
        RtAudioStreamState *m_state{};
    };
}
#endif
