#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Log.hpp"
#include "util/Path.hpp"
#include "resource/Resource.hpp"
#include "resource/ResourceEnum.hpp"

namespace ATMA
{
    /**
     * Resource sub-class for sound .wav files to allow the AudioWave to managed
     * by the context
     */
    class Wave: public Resource
    {
    public:
        // constructor specifing name, path, and source code
        Wave(
            const std::string &l_name,
            const Path &l_path,
            const unsigned short &l_channels,
            const unsigned int &l_sampleRate,
            const size_t &l_sampleSize,
            const std::vector<unsigned char> &l_data
        ):
            Resource(l_name, l_path, ResType(ResourceEnum::Waveform)),
            m_channels(l_channels),
            m_sampleRate(l_sampleRate),
            m_sampleSize(l_sampleSize),
            m_data(l_data)
        {
        }

        // default constructor
        Wave():
            Resource("", Path{""}, ResType(ResourceEnum::Waveform)),
            m_channels(0),
            m_sampleRate(0),
            m_sampleSize(0),
            m_data(std::vector<unsigned char>{})
        {
        }

        const unsigned short m_channels;
        const size_t m_sampleSize;
        const unsigned int m_sampleRate;
        std::vector<unsigned char> m_data;
    };

    class AudioWave: public LoadedResource
    {
    public:
        virtual ~AudioWave();
        AudioWave(const Wave &l_wave);
        const Wave m_wave;
    };
}
