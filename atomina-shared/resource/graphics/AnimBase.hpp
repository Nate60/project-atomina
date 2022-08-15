#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{
    using FrameId = unsigned int;

    class ATMA_API AnimBase
    {
    public:
        AnimBase(
            const std::string &l_name,
            const unsigned int &m_width,
            const unsigned int &m_height,
            const unsigned int &l_sheetLine = 0,
            const unsigned int &l_startFrame = 0,
            const unsigned int &l_endFrame = 0,
            const unsigned int &l_activeStart = 0,
            const unsigned int &l_activeEnd = 0,
            const bool &l_loop = false
        );

        AnimBase(
            const std::string &l_name,
            const sf::Vector2u &l_dimensions,
            const unsigned int &l_sheetLine = 0,
            const unsigned int &l_startFrame = 0,
            const unsigned int &l_endFrame = 0,
            const unsigned int &l_activeStart = 0,
            const unsigned int &l_activeEnd = 0,
            const bool &l_loop = false
        );

        const std::string m_name;
        const unsigned int m_width;
        const unsigned int m_height;
        const FrameId m_startFrame;
        const FrameId m_endFrame;
        const FrameId m_activeStart;
        const FrameId m_activeEnd;
        const FrameId m_sheetLine;
        const bool m_loop;

        bool m_playing{false};

        virtual void update(float l_dt);

        virtual const unsigned int getCurrentFrameId() const;
    protected:
        virtual void step() = 0;
        FrameId m_currentFrame{0};
    };

}