#pragma once
#include "math/Vec2.hpp"
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/Resource.hpp"
#include "util/ATConst.hpp"
#include <limits>

namespace ATMA
{
    using FrameId = unsigned int;

    struct FrameData
    {
        const unsigned short m_ticks;
        const std::bitset<ATConst::BITSET_SIZE> m_flags;
    };

    struct AnimationData
    {
        const std::string m_name;
        const unsigned int m_frameCount;
        const unsigned int m_sheetWidth;
        const Vec2<float> m_frameSize{0.f, 0.f};
        const Vec2<float> m_startPos{0.f, 0.f};
        const std::vector<FrameData> m_frameData{};
        const bool m_loop{false};
    };

    /**
     * Animation superclass that defines behaviour of
     * all animation objects
     */
    class Animation: public LoadedResource
    {
    public:
        // constructor specifying all parameters

        Animation(const AnimationData &data);
        virtual ~Animation();
        const AnimationData m_data;
        /**
         * updates the animation timer according to the time
         * given
         * @param l_dt time since last update
         */
        virtual void update(const double &l_dt);

        /**
         * gets the current frame id of the animation
         * @returns frame index of the current frame
         */
        virtual const unsigned int getCurrentFrameId() const;

        const Vec2<float> &getAdv() const;
    protected:
        /**
         * advances the animation one frame
         */
        virtual void step();

        double m_dt;
        unsigned short m_tick;
        FrameId m_currentFrame{0};
        Vec2<float> m_adv{0.f, 0.f};
    };

}
