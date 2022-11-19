#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/attributes/AttrGraphic.hpp"
#include "OAS/attributes/AttrAnimation.hpp"
#include "OAS/System.hpp"

namespace ATMA
{

    class ATMA_API SysAnimator: public SysBase
    {
    public:
        SysAnimator();

        virtual void update(const float &l_dt) override;

        virtual void notify(const ObjectEventContext &l_e) override;
    };

}