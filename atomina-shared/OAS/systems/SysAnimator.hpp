#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/System.hpp"
#include "core/ATMAContext.hpp"

namespace ATMA
{
    /**
     * System that implements render calls on all objects that can be rendered
     */
    class SysAnimator: public SysBase
    {
    public:
        // default constructor
        SysAnimator();

        // deconstructor
        virtual ~SysAnimator();

        /**
         * update internal members on an engine tick basis
         * @param l_dt the time since last update
         */
        virtual void update(ATMAContext *l_ctx, const double &l_dt) override;

        /**
         * event callback function where the system will changes
         * its behaviour or perform an action based on the event details
         * @param l_e details of the event
         */
        virtual void notify(ATMAContext *l_ctx, const ObjectEventContext &l_e) override;
    };

}
