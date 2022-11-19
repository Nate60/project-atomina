#pragma once
#include "pch.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/System.hpp"
#include "OAS/attributes/AttrPosition.hpp"
#include "OAS/attributes/AttrVelocity.hpp"
#include "OAS/Attribute.hpp"
#include "core/api.hpp"

namespace ATMA
{

    class ATMA_API SysTranslator: public SysBase
    {
    public:
        SysTranslator();

        ~SysTranslator();

        void update(const float &l_dt) override;

        virtual void notify(const ObjectEventContext &l_e) override;
    };

}