#include "pipewire/thread-loop.h"
#ifdef __linux__
#    include "pipewire/core.h"
#    include "pipewire/keys.h"
#    include "pipewire/main-loop.h"
#    include "pipewire/port.h"
#    include "pipewire/properties.h"
#    include "pipewire/proxy.h"
#    include "pipewire/stream.h"
#    include "spa/param/param.h"
#    include "spa/utils/hook.h"
#    include "spa/pod/builder.h"
#    include "spa/param/audio/raw.h"
#    include "spa/param/audio/format-utils.h"
#    include "util/Log.hpp"
#    include "pch.hpp"
#    include "core/ATMAContext.hpp"
#    include "resource/ResourceManager.hpp"
#    include "sound/AudioWave.hpp"
#    include "AudioChannelUnixImpl.hpp"

namespace ATMA
{

    static void onProcess(void *userData)
    {
        PipewireStreamState *d = (PipewireStreamState *)userData;
        pw_buffer *b;
        spa_buffer *buf;
        unsigned int i = 0;
        int frameCount, stride;
        int16_t *dst, val;

        pw_thread_loop_lock(d->m_threadLoop);
        if((b = pw_stream_dequeue_buffer(d->m_stream)) == NULL)
        {
            pw_log_warn("out of buffers: %m");
            pw_thread_loop_unlock(d->m_threadLoop);
            return;
        }

        buf = b->buffer;
        if((dst = (int16_t *)buf->datas[0].data) == NULL)
        {
            ATMA_ENGINE_INFO("onProcess done, no data");
            pw_thread_loop_unlock(d->m_threadLoop);
            return;
        }

        stride = sizeof(int16_t) * d->m_channels;
        frameCount = buf->datas[0].maxsize / stride;
        if(b->requested)
        {
            frameCount = SPA_MIN(b->requested, frameCount);
        }
        unsigned int sampleCount = frameCount * d->m_channels;
        {
            std::lock_guard<std::mutex> lock{d->m_lock};
            if(!d->m_soundQueue.empty())
            {
                auto res = d->ctx->m_resMan->loadResource<ATMA::AudioWave>(d->m_soundQueue.front());

                // Write interleaved audio data.
                unsigned short *data = (unsigned short *)res->m_wave.m_data.data();

                for(; i < sampleCount; ++i)
                {
                    if(d->m_sampleIndex >= res->m_wave.m_data.size() / 2)
                    {
                        if(d->m_soundQueue.size() > 1)
                        {
                            res = d->ctx->m_resMan->loadResource<ATMA::AudioWave>(d->m_soundQueue.front());
                            d->m_soundQueue.pop();
                            d->m_sampleIndex = 0;
                            d->m_chunkIndex = 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                    *dst++ = data[d->m_sampleIndex++];
                }
            }
        }
        ATMA_ENGINE_TRACE("played {} samples", i);
        for(; i < sampleCount; ++i)
        {
            *dst++ = 0;
        }
        buf->datas[0].chunk->offset = 0;
        buf->datas[0].chunk->stride = stride;
        buf->datas[0].chunk->size = frameCount * stride;

        pw_stream_queue_buffer(d->m_stream, b);
        pw_thread_loop_unlock(d->m_threadLoop);
    }

    static const pw_stream_events streamEvents = pw_stream_events{
        PW_VERSION_STREAM_EVENTS,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        &onProcess
    };

    AudioChannelUnixImpl::AudioChannelUnixImpl(
        ATMAContext *ctx,
        const unsigned int &l_bufferSize,
        const unsigned int &l_channelCount,
        const AudioFrequency &l_freq
    ):
        AudioChannel(l_bufferSize, l_channelCount, l_freq),
        m_streamState(PipewireStreamState{ctx, (const int16_t)l_channelCount, 1.0f, (const int)l_freq})
    {
        std::string headerVersion = std::string{pw_get_headers_version()};
        std::string libraryVersion = std::string{pw_get_library_version()};
        spa_audio_info_raw rawInfo =
            SPA_AUDIO_INFO_RAW_INIT(SPA_AUDIO_FORMAT_S16, 0, static_cast<unsigned int>(l_freq), l_channelCount);

        const spa_pod *params[1];
        uint8_t buffer[1024];
        int streamFlags = PW_STREAM_FLAG_AUTOCONNECT | PW_STREAM_FLAG_MAP_BUFFERS | PW_STREAM_FLAG_RT_PROCESS;
        spa_pod_builder b = SPA_POD_BUILDER_INIT(buffer, sizeof(buffer));
        params[0] = spa_format_audio_raw_build(&b, SPA_PARAM_EnumFormat, &rawInfo);

        pw_init(ctx->argc, &ctx->argv);
        ATMA_ENGINE_INFO("compiled pipewire {} linked with pipewire {}", headerVersion.c_str(), libraryVersion.c_str());
        m_streamState.m_threadLoop = pw_thread_loop_new("pipewire-main", NULL);
        m_streamState.m_stream = pw_stream_new_simple(
            pw_thread_loop_get_loop(m_streamState.m_threadLoop),
            "audio-src",
            pw_properties_new(
                PW_KEY_MEDIA_TYPE, "Audio", PW_KEY_MEDIA_CATEGORY, "Playback", PW_KEY_MEDIA_ROLE, "Music", NULL
            ),
            &streamEvents,
            &m_streamState
        );
        pw_stream_connect(
            m_streamState.m_stream, PW_DIRECTION_OUTPUT, PW_ID_ANY, static_cast<pw_stream_flags>(streamFlags), params, 1
        );

        pw_thread_loop_start(m_streamState.m_threadLoop);
    }

    AudioChannelUnixImpl::~AudioChannelUnixImpl()
    {
        pw_thread_loop_stop(m_streamState.m_threadLoop);
        pw_thread_loop_lock(m_streamState.m_threadLoop);
        pw_stream_destroy(m_streamState.m_stream);
        pw_thread_loop_destroy(m_streamState.m_threadLoop);
        pw_thread_loop_unlock(m_streamState.m_threadLoop);
    }

    void AudioChannelUnixImpl::pushSound(const unsigned int &l_id)
    {
        std::lock_guard<std::mutex> lock{m_streamState.m_lock};
        m_streamState.m_soundQueue.push(l_id);
    }

    void AudioChannelUnixImpl::playNow(const unsigned int &l_id)
    {
        std::lock_guard<std::mutex> lock{m_streamState.m_lock};
        m_streamState.m_soundQueue = std::queue<unsigned int>{};
        m_streamState.m_soundQueue.push(l_id);
        m_streamState.m_chunkIndex = 0;
        m_streamState.m_sampleIndex = 0;
    }
}
#endif
