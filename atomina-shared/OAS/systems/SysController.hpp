#pragma once
#include "core/ATMAContext.hpp"
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/attributes/AttrShape.hpp"
#include "OAS/System.hpp"

namespace ATMA
{
    /**
     * System that implements input control for objects allows for user inputs
     * to affect objects
     */
    class SysController: public SysBase
    {
    public:
        // default constructor
        SysController();

        // deconstructor
        virtual ~SysController();

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
