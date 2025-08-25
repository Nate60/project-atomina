#include "pch.hpp"
#include "AudioWaveLoader.hpp"

namespace ATMA
{
    ResourceLoader<AudioWave>::ResourceLoader() {}

    ResourceLoader<AudioWave>::~ResourceLoader() {}

    std::shared_ptr<AudioWave> ResourceLoader<AudioWave>::load(const std::string &l_name, const Path &l_path)
    {
        std::basic_ifstream<char> audioFile{l_path.toString(), std::ios_base::binary};
        std::vector<char> buffer;
        audioFile.seekg(0, audioFile.end);
        size_t length = audioFile.tellg();
        audioFile.seekg(0, audioFile.beg);
        if(length > 0)
        {
            ATMA_ENGINE_TRACE("Audio loading buffer size: {}", length);
            buffer.resize(length);
            audioFile.exceptions(std::ios::failbit | std::ios::badbit);
            try
            {
                audioFile.read(&buffer[0], length);
            }
            catch(const std::bad_cast &e)
            {
                ATMA_ENGINE_ERROR("failed to cast: {}", e.what());
                return nullptr;
            }
            catch(const std::ios_base::failure &e)
            {
                ATMA_ENGINE_ERROR("failed to read file {} : {}", l_path.toString().c_str(), e.what());
                return nullptr;
            }
            unsigned int formatChunkSize{};
            unsigned short format{};
            unsigned short channels{};
            unsigned int sampleRate{};
            unsigned short sampleSize{};
            unsigned int dataSize{};
            std::copy(
                buffer.begin() + 16,
                buffer.begin() + 16 + sizeof(unsigned int),
                reinterpret_cast<unsigned char *>(&formatChunkSize)
            );
            std::copy(
                buffer.begin() + 20,
                buffer.begin() + 20 + sizeof(unsigned short),
                reinterpret_cast<unsigned char *>(&format)
            );
            std::copy(
                buffer.begin() + 22,
                buffer.begin() + 22 + sizeof(unsigned short),
                reinterpret_cast<unsigned char *>(&channels)
            );
            std::copy(
                buffer.begin() + 24,
                buffer.begin() + 24 + sizeof(unsigned int),
                reinterpret_cast<unsigned char *>(&sampleRate)
            );
            std::copy(
                buffer.begin() + 34,
                buffer.begin() + 34 + sizeof(unsigned short),
                reinterpret_cast<unsigned char *>(&sampleSize)
            );
            std::copy(
                buffer.begin() + 40,
                buffer.begin() + 40 + sizeof(unsigned int),
                reinterpret_cast<unsigned char *>(&dataSize)
            );

            std::vector<unsigned char> data{};
            data.reserve(dataSize);
            for(int i = 0; i < dataSize; i++)
            {
                data.emplace_back(buffer[44 + i]);
            }
            audioFile.close();
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
        return nullptr;
    }

    std::shared_ptr<AudioWave> ResourceLoader<AudioWave>::load(const std::string &l_name)
    {
        Wave w{l_name, ATMA::Path{""}, 0, 0, 0, {}};
        return std::make_shared<AudioWave>(w);
    }

}
