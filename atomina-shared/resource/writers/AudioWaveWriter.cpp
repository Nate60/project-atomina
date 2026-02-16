#include "pch.hpp"
#include "AudioWaveWriter.hpp"

namespace ATMA
{
    ResourceWriter<AudioWave>::ResourceWriter() {}

    ResourceWriter<AudioWave>::~ResourceWriter() {}

    void ResourceWriter<AudioWave>::write(const std::shared_ptr<AudioWave> l_res, const Path &l_path)
    {
        std::basic_ofstream<char> waveFile{l_path.toString(), std::ios_base::binary};
        waveFile.exceptions(std::ios::failbit | std::ios::badbit);
        // TODO: A-144
        long long clear = 0ll;
        unsigned int clearInt = 0u;
        unsigned int formatChunkSize = 0u;
        unsigned short formatChunkTag = 0u;
        unsigned int dataSize = l_res->m_wave.m_data.size();
        waveFile.write(reinterpret_cast<const char *>(&clear), sizeof(long long));                         // stride: 0
        waveFile.write(reinterpret_cast<const char *>(&clear), sizeof(long long));                         // stride: 8
        waveFile.write(reinterpret_cast<const char *>(&formatChunkSize), sizeof(unsigned int));            // stride: 16
        waveFile.write(reinterpret_cast<const char *>(&formatChunkTag), sizeof(unsigned short));           // stride: 20
        waveFile.write(reinterpret_cast<const char *>(&l_res->m_wave.m_channels), sizeof(unsigned short)); // stride: 22
        waveFile.write(
            reinterpret_cast<const char *>(&l_res->m_wave.m_sampleRate), sizeof(unsigned short)
        );                                                                         // stride: 24
        waveFile.write(reinterpret_cast<const char *>(&clear), sizeof(long long)); // stride: 26
        waveFile.write(
            reinterpret_cast<const char *>(&l_res->m_wave.m_sampleSize), sizeof(unsigned short)
        );                                                                               // stride: 34
        waveFile.write(reinterpret_cast<const char *>(&clearInt), sizeof(unsigned int)); // stride: 36
        waveFile.write(reinterpret_cast<const char *>(&dataSize), sizeof(unsigned int)); // stride: 40
        for(unsigned int i = 0; i < dataSize; i++)
        {
            waveFile.write(reinterpret_cast<const char *>(&l_res->m_wave.m_data[i]), sizeof(unsigned char));
        }
        ATMA_ENGINE_INFO(
            "wrote {} channels={} sampleRate={} sampleSize={} dataSize={}",
            l_path.toString().c_str(),
            l_res->m_wave.m_channels,
            l_res->m_wave.m_sampleRate,
            l_res->m_wave.m_sampleSize,
            l_res->m_wave.m_data.size()
        );
    }

}
