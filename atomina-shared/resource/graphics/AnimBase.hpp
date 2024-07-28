#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{
    using FrameId = unsigned int;

    /**
     * Animation superclass that defines behaviour of
     * all animation objects
     */
    class AnimBase
    {
    public:
        // constructor specifying all parameters
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

        /**
         * updates the animation timer according to the time
         * given
         * @param l_dt time since last update
         */
        virtual void update(float l_dt);

        /**
         * gets the current frame id of the animation
         * @returns frame index of the current frame
         */
        virtual const unsigned int getCurrentFrameId() const;
    protected:
        /**
         * advances the animation one frame
         */
        virtual void step() = 0;

        FrameId m_currentFrame{0};
    };

}