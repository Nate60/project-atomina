#include "pch.hpp"
#include "AudioWaveLoader.hpp"
#include "file/FileFuncs.hpp"

namespace ATMA
{
    ResourceLoader<AudioWave>::ResourceLoader() {}

    ResourceLoader<AudioWave>::~ResourceLoader() {}

    std::shared_ptr<AudioWave> ResourceLoader<AudioWave>::load(
        ATMAContext *l_ctx,
        const std::string &l_name,
        const Path &l_path,
        std::vector<char> &l_buffer,
        size_t &l_bytes
    )
    {
        unsigned int formatChunkSize{};
        unsigned short format{};
        unsigned short channels{};
        unsigned int sampleRate{};
        unsigned short sampleSize{};
        unsigned int dataSize{};
        l_bytes = 16ul;
        move(l_buffer, l_bytes, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&formatChunkSize));
        move(l_buffer, l_bytes, sizeof(unsigned short), reinterpret_cast<unsigned char *>(&format));
        move(l_buffer, l_bytes, sizeof(unsigned short), reinterpret_cast<unsigned char *>(&channels));
        move(l_buffer, l_bytes, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&sampleRate));
        l_bytes = 34ul;
        move(l_buffer, l_bytes, sizeof(unsigned short), reinterpret_cast<unsigned char *>(&sampleSize));
        l_bytes = 40ul;
        move(l_buffer, l_bytes, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&dataSize));
        std::vector<unsigned char> data{};
        data.reserve(dataSize);
        for(size_t i = 0; i < dataSize; i++)
        {
            data.emplace_back(l_buffer[l_bytes + i]);
        }
        ATMA_ENGINE_INFO(
            "loaded {} formatChunkSize={} format={} channels={} sampleRate={} sampleSize={} dataSize={}",
            l_path.toString().c_str(),
            formatChunkSize,
            format,
            channels,
            sampleRate,
            sampleSize,
            dataSize
        );
        Wave w{l_name, l_path, channels, sampleRate, sampleSize / size_t(8), data};
        return std::make_shared<AudioWave>(w);
    }

    std::shared_ptr<AudioWave> ResourceLoader<AudioWave>::load(ATMAContext *l_ctx, const std::string &l_name)
    {
        Wave w{l_name, ATMA::Path{""}, 0, 0, 0, {}};
        return std::make_shared<AudioWave>(w);
    }

}
