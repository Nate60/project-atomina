#ifdef __linux__
#    include "pch.hpp"
#    include "sound/AudioChannel.hpp"
#    include "util/Log.hpp"

namespace ATMA
{

    static void onProcess(void *userData);

    struct PipewireStreamState
    {
        const int16_t m_channels;
        const float m_volume;
        const int m_freq;
        unsigned int m_chunkIndex{};
        unsigned int m_sampleIndex{};
        std::mutex m_lock;
        pw_thread_loop *m_threadLoop;
        pw_stream *m_stream;
        std::queue<unsigned int> m_soundQueue{};
    };

    class AudioChannelUnixImpl: public AudioChannel
    {
    public:
        AudioChannelUnixImpl(
            const unsigned int &l_bufferSize = 1024u,
            const unsigned int &l_channelCount = 2u,
            const AudioFrequency &l_freq = AudioFrequency::FREQ_44100
        );

        virtual ~AudioChannelUnixImpl();

        virtual void pushSound(const unsigned int &l_id);

        virtual void playNow(const unsigned int &l_id);
        PipewireStreamState m_streamState{};
    protected:
    };

}
#endif
