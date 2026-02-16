#include "pch.hpp"
#include "util/ATConst.hpp"
#include "Animation.hpp"

namespace ATMA
{
    FrameData::FrameData(const unsigned short &l_ticks, const std::bitset<ATConst::BITSET_SIZE> &l_flags):
        m_ticks(l_ticks),
        m_flags(l_flags)
    {
    }

    FrameData::FrameData(const FrameData &l_other): m_ticks(l_other.m_ticks), m_flags(l_other.m_flags) {}

    FrameData::FrameData(FrameData &&l_other): m_ticks(std::move(l_other.m_ticks)), m_flags(std::move(l_other.m_flags))
    {
    }

    const unsigned short &FrameData::ticks() const
    {
        return this->m_ticks;
    }

    const std::bitset<ATConst::BITSET_SIZE> &FrameData::flags() const
    {
        return this->m_flags;
    }

    void FrameData::operator=(const FrameData &l_other)
    {
        this->m_ticks = l_other.m_ticks;
        this->m_flags = l_other.m_flags;
    }

    void FrameData::operator=(FrameData &&l_other)
    {
        this->m_ticks = std::move(l_other.m_ticks);
        this->m_flags = std::move(l_other.m_flags);
    }

    AnimationData::AnimationData(
        const std::string &l_name,
        const unsigned int &l_frameCount,
        const unsigned int &l_sheetWidth,
        const Vec2<float> &l_frameSize,
        const Vec2<float> &l_startPos,
        const std::vector<FrameData> &l_frameData,
        const bool &l_loop
    ):
        m_name(l_name),
        m_frameCount(l_frameCount),
        m_sheetWidth(l_sheetWidth),
        m_frameSize(l_frameSize),
        m_startPos(l_startPos),
        m_frameData(l_frameData),
        m_loop(l_loop)
    {
    }

    AnimationData::AnimationData(const AnimationData &l_other):
        m_name(l_other.m_name),
        m_frameCount(l_other.m_frameCount),
        m_sheetWidth(l_other.m_sheetWidth),
        m_frameSize(l_other.m_frameSize),
        m_startPos(l_other.m_startPos),
        m_frameData(l_other.m_frameData),
        m_loop(l_other.m_loop)
    {
    }

    AnimationData::AnimationData(AnimationData &&l_other):
        m_name(std::move(l_other.m_name)),
        m_frameCount(std::move(l_other.m_frameCount)),
        m_sheetWidth(std::move(l_other.m_sheetWidth)),
        m_frameSize(std::move(l_other.m_frameSize)),
        m_startPos(std::move(l_other.m_startPos)),
        m_frameData(std::move(l_other.m_frameData)),
        m_loop(std::move(l_other.m_loop))
    {
    }

    void AnimationData::operator=(const AnimationData &l_other)
    {
        this->m_name = l_other.m_name;
        this->m_frameCount = l_other.m_frameCount;
        this->m_sheetWidth = l_other.m_sheetWidth;
        this->m_frameSize = l_other.m_frameSize;
        this->m_startPos = l_other.m_startPos;
        this->m_frameData = l_other.m_frameData;
        this->m_loop = l_other.m_loop;
    }

    void AnimationData::operator=(AnimationData &&l_other)
    {
        this->m_name = std::move(l_other.m_name);
        this->m_frameCount = std::move(l_other.m_frameCount);
        this->m_sheetWidth = std::move(l_other.m_sheetWidth);
        this->m_frameSize = std::move(l_other.m_frameSize);
        this->m_startPos = std::move(l_other.m_startPos);
        this->m_frameData = std::move(l_other.m_frameData);
        this->m_loop = std::move(l_other.m_loop);
    }

    const std::string &AnimationData::name() const
    {
        return this->m_name;
    }

    const unsigned int &AnimationData::frameCount() const
    {
        return this->m_frameCount;
    }

    const unsigned int &AnimationData::sheetWidth() const
    {
        return this->m_sheetWidth;
    }

    const Vec2<float> &AnimationData::frameSize() const
    {
        return this->m_frameSize;
    }

    const Vec2<float> &AnimationData::startPos() const
    {
        return this->m_startPos;
    }

    const std::vector<FrameData> &AnimationData::frameData() const
    {
        return this->m_frameData;
    }

    const bool &AnimationData::loop() const
    {
        return this->m_loop;
    }

    Animation::Animation(const Animation &l_other): m_data(l_other.m_data) {}

    Animation::Animation(Animation &&l_other): m_data(std::move(l_other.m_data)) {}

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

    const AnimationData &Animation::data() const
    {
        return this->m_data;
    }

    void Animation::operator=(const Animation &l_other)
    {
        this->m_data = l_other.m_data;
    }

    void Animation::operator=(Animation &&l_other)
    {
        this->m_data = std::move(l_other.m_data);
    }

}
