#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/attributes/AttrPosition.hpp"
#include "OAS/System.hpp"

namespace ATMA
{

    class ATMA_API SysController: public SysBase
    {
    public:
        SysController();

        virtual void update(const float &l_dt) override;

        virtual void notify(const ObjectEventContext &l_e) override;
    };

}
