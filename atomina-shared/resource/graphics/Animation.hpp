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
        FrameData(const unsigned short &l_ticks, const std::bitset<ATConst::BITSET_SIZE> &m_flags);

        FrameData(const FrameData &l_other);

        FrameData(FrameData &&l_other);

        void operator=(const FrameData &l_other);
        void operator=(FrameData &&l_other);
        const unsigned short &ticks() const;
        const std::bitset<ATConst::BITSET_SIZE> &flags() const;
    protected:
        unsigned short m_ticks;
        std::bitset<ATConst::BITSET_SIZE> m_flags;
        friend struct AnimationData;
        friend class Animation;
    };

    struct AnimationData
    {
        AnimationData(
            const std::string &l_name,
            const unsigned int &l_frameCount,
            const unsigned int &l_sheetWidth,
            const Vec2<float> &l_frameSize = {0.f, 0.f},
            const Vec2<float> &l_startPos = {0.f, 0.f},
            const std::vector<FrameData> &l_frameData = {},
            const bool &l_loop = {false}
        );

        AnimationData(const AnimationData &l_other);
        AnimationData(AnimationData &&l_other);

        void operator=(const AnimationData &l_other);
        void operator=(AnimationData &&l_other);

        const std::string &name() const;
        const unsigned int &frameCount() const;
        const unsigned int &sheetWidth() const;
        const Vec2<float> &frameSize() const;
        const Vec2<float> &startPos() const;
        const std::vector<FrameData> &frameData() const;
        const bool &loop() const;
    protected:
        std::string m_name;
        unsigned int m_frameCount;
        unsigned int m_sheetWidth;
        Vec2<float> m_frameSize{0.f, 0.f};
        Vec2<float> m_startPos{0.f, 0.f};
        std::vector<FrameData> m_frameData{};
        bool m_loop{false};
        friend class Animation;
    };

    /**
     * Animation superclass that defines behaviour of
     * all animation objects
     */
    class Animation: public LoadedResource
    {
    public:
        // constructor specifying all parameters

        Animation(const Animation &l_other);
        Animation(Animation &&l_other);
        Animation(const AnimationData &data);
        virtual ~Animation();
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

        // Copy Constructor
        void operator=(const Animation &l_other);

        // Move Constructor
        void operator=(Animation &&l_other);

        const AnimationData &data() const;
    protected:
        /**
         * advances the animation one frame
         */
        virtual void step();

        AnimationData m_data;
        double m_dt;
        unsigned short m_tick;
        FrameId m_currentFrame{0};
        Vec2<float> m_adv{0.f, 0.f};
    };

}
