#include "pch.hpp"
#include "util/ATConst.hpp"
#include "Animation.hpp"

namespace ATMA
{

    Animation::Animation(const AnimationData &data): m_data(data) {}

    Animation::~Animation() {}

    void Animation::update(const double &l_dt)
    {
        m_dt += l_dt;
        if(l_dt >= ATConst::TICK_RATE)
        {
            step();
            m_dt -= ATConst::TICK_RATE;
        }
    }

    const unsigned int Animation::getCurrentFrameId() const
    {
        return m_currentFrame;
    }

    const Vec2<float> &Animation::getAdv() const
    {
        return m_adv;
    }

    void Animation::step()
    {
        m_tick += 1;
        if(m_data.m_frameData[m_currentFrame].m_ticks <= m_tick)
        {
            m_tick = 0;
            m_currentFrame++;
            if(m_currentFrame >= m_data.m_frameCount)
            {
                m_currentFrame = 0;
                m_adv = {0.f, 0.f};
            }
            else if(m_adv.x + m_data.m_startPos.x + m_data.m_frameSize.x >= m_data.m_frameSize.x * m_data.m_sheetWidth)
            {
                m_adv.x = 0.f;
                // origin is bottom-left, we read top to bottom
                m_adv.y -= m_data.m_frameSize.y;
            }
            else [[likely]]
            {
                m_adv.x += m_data.m_frameSize.x;
            }
        }
    }

}
