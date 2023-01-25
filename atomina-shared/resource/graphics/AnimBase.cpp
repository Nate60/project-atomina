#include "pch.hpp"
#include "AnimBase.hpp"

namespace ATMA
{

    AnimBase::AnimBase(
        const std::string &l_name,
        const unsigned int &l_width,
        const unsigned int &l_height,
        const unsigned int &l_sheetLine,
        const unsigned int &l_startFrame,
        const unsigned int &l_endFrame,
        const unsigned int &l_activeStart,
        const unsigned int &l_activeEnd,
        const bool &l_loop
    ):
        m_name(l_name),
        m_startFrame(l_startFrame),
        m_endFrame(l_endFrame),
        m_activeStart(l_activeStart),
        m_activeEnd(l_activeEnd),
        m_loop(l_loop),
        m_width(l_width),
        m_height(l_height),
        m_sheetLine(l_sheetLine)
    {
    }

    void AnimBase::update(float l_dt)
    {
        if(l_dt >= 1)
            step();
    }

    const unsigned int AnimBase::getCurrentFrameId() const
    {
        return m_currentFrame;
    }

}