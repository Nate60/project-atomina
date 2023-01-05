#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/graphics/AnimBase.hpp"

namespace ATMA
{

    /**
     * Basic animation only having one frame
     */
    class ATMA_API AnimDefault: public AnimBase
    {
    public:
        AnimDefault();
    protected:
        /**
         * advances the frame index 
         */
        virtual void step() override;
    };

}