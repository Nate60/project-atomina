#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/attributes/AttrDrawable.hpp"
#include "OAS/attributes/AttrAnimatable.hpp"
#include "OAS/System.hpp"

namespace ATMA
{

    class ATMA_API SysAnimator: public SysBase
    {
    public:
        SysAnimator();

        virtual void update(const float &l_dt) override;
    };

}