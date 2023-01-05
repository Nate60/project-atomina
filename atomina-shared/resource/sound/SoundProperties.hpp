#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * structure containing all information about sound 
     */
    struct ATMA_API SoundProperties
    {
        SoundProperties(const std::string &l_name):
            m_name(l_name),
            m_volume(100),
            m_pitch(1.0f),
            m_range(10.0f),
            m_attenuation(10.0f)
        {
        }

        std::string m_name;
        float m_volume;
        float m_pitch;
        float m_range;
        float m_attenuation;
    };

}