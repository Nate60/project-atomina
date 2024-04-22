#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/System.hpp"
#include "OAS/attributes/AttrLabel.hpp"
#include "core/ATMAContext.hpp"

namespace ATMA
{
    /**
     * System that implements input control for objects allows for user inputs
     * to affect objects
     */
    class ATMA_API SysTextRenderer: public SysBase
    {
    public:
        // default constructor
        SysTextRenderer();

        // deconstructor
        virtual ~SysTextRenderer();

        /**
         * update internal members on an engine tick basis
         * @param l_dt the time since last update
         */
        virtual void update(const float &l_dt) override;

        /**
         * event callback function where the system will changes
         * its behaviour or perform an action based on the event details
         * @param l_e details of the event
         */
        virtual void notify(const ObjectEventContext &l_e) override;
    };

}
