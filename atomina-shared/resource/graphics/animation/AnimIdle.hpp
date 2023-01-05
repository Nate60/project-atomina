#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/graphics/AnimBase.hpp"

namespace ATMA
{

    /**
     * Animation for any object that is idle 
     */
    class ATMA_API AnimIdle: public AnimBase
    {
    public:

        //constructor specifying all parameters
        AnimIdle(
            const std::string &l_name,
            const unsigned int &l_width,
            const unsigned int &l_height,
            const unsigned int &l_sheetLine = 0,
            const unsigned int &l_startFrame = 0,
            const unsigned int &l_endFrame = 0,
            const unsigned int &l_activeStart = 0,
            const unsigned int &l_activeEnd = 0,
            const bool &l_loop = false
        );

        //constructor specifying all parameters with vector for dimensions
        AnimIdle(
            const std::string &l_name,
            const sf::Vector2u &l_dimensions,
            const unsigned int &l_sheetLine = 0,
            const unsigned int &l_startFrame = 0,
            const unsigned int &l_endFrame = 0,
            const unsigned int &l_activeStart = 0,
            const unsigned int &l_activeEnd = 0,
            const bool &l_loop = false
        );
    protected:

        /**
         * advances the frame index of the animation 
         */
        virtual void step() override;
    };

}