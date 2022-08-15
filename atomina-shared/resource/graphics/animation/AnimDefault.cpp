#include "pch.hpp"
#include "AnimDefault.hpp"

namespace ATMA
{
    AnimDefault::AnimDefault(): AnimBase("Default", 32, 32, 0, 0, 0, 0, 0, true) {}

    void AnimDefault::step()
    {
        ++m_currentFrame;
        if(m_currentFrame > m_endFrame)
            m_currentFrame = 0;
    }

}
