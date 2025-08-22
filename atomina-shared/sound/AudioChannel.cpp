#include "pch.hpp"
#include "AudioChannel.hpp"
#include "util/Log.hpp"
#ifdef _WINDOWS
#    include "platform/Win/sound/AudioChannelWinImpl.hpp"
#    define __ATMAMAKEAUDIOCHANNEL(ctx, size, count, freq)                                                             \
        return std::make_shared<AudioChannelWinImpl>(ctx, size, count, freq)
#elif __linux__
#    include "platform/Linux/sound/AudioChannelUnixImpl.hpp"
#    define __ATMAMAKEAUDIOCHANNEL(ctx, size, count, freq)                                                             \
        return std::make_shared<AudioChannelUnixImpl>(ctx, size, count, freq)
#endif

namespace ATMA
{

    AudioChannel::AudioChannel(
        const unsigned int &l_bufferSize,
        const unsigned int &l_channelCount,
        const AudioFrequency &l_freq
    ):
        m_bufferSize(l_bufferSize),
        m_channelCount(l_channelCount),
        m_freq(l_freq)
    {
    }

    AudioChannel::~AudioChannel() {}

    std::shared_ptr<AudioChannel> AudioChannel::makeAudioChannel(
        ATMAContext *l_ctx,
        const unsigned int &l_bufferSize,
        const unsigned int &l_channelCount,
        const AudioFrequency &l_freq
    )
    {
        __ATMAMAKEAUDIOCHANNEL(l_ctx, l_bufferSize, l_channelCount, l_freq);
    }

    void AudioChannel::pushSound(const unsigned int &l_id) {}

    void AudioChannel::playNow(const unsigned int &l_id) {}

}
