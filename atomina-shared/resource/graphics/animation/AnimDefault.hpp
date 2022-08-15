#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/graphics/AnimBase.hpp"

namespace ATMA
{

    class ATMA_API AnimDefault: public AnimBase
    {
    public:
        AnimDefault();
    protected:
        virtual void step() override;
    };

}