#include "pch.hpp"
#include "AnimIdle.hpp"

namespace ATMA
{
    AnimIdle::AnimIdle(
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
        AnimBase(
            l_name,
            l_width,
            l_height,
            l_sheetLine,
            l_startFrame,
            l_endFrame,
            l_activeStart,
            l_activeEnd,
            l_loop
        )
    {
    }

    AnimIdle::AnimIdle(
        const std::string &l_name,
        const sf::Vector2u &l_dimensions,
        const unsigned int &l_sheetLine,
        const unsigned int &l_startFrame,
        const unsigned int &l_endFrame,
        const unsigned int &l_activeStart,
        const unsigned int &l_activeEnd,
        const bool &l_loop
    ):
        AnimBase(
            l_name,
            l_dimensions,
            l_sheetLine,
            l_startFrame,
            l_endFrame,
            l_activeStart,
            l_activeEnd,
            l_loop
        )
    {
    }

    void AnimIdle::step()
    {
        ++m_currentFrame;
        if(m_currentFrame > m_endFrame)
            m_currentFrame = 0;
    }

}
