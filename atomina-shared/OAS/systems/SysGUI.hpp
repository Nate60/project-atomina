#pragma once
#include "OAS/SysBase.hpp"
#include "event/ObjectEventContext.hpp"
#include "OAS/attributes/AttrMouseRegion.hpp"
#include "OAS/attributes/AttrMouseTrigger.hpp"
#include "OAS/System.hpp"
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    class ATMA_API SysGUI: public SysBase
    {
    public:
        SysGUI();
        ~SysGUI();

        virtual void update(const float &l_dt) override;
        virtual void notify(const ObjectEventContext &l_e) override;
    };

}