#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/System.hpp"
#include "OAS/attributes/AttrCollidable.hpp"
#include "math/Stadium.hpp"
#include "util/Props.hpp"
#include "event/ObjectEventContext.hpp"
#include "event/ObjectEvent.hpp"

namespace ATMA{

    /**
     * System that implements collision detection for all collideable objects
     */
    class ATMA_API SysCollider: public SysBase
    {
    public:
        // default constructor
        SysCollider();

        // deconstructor
        virtual ~SysCollider();

        /**
         * update internal members on an engine tick basis
         * @param l_dt the time since last update
         */
        virtual void update(const long long &l_dt) override;

        /**
         * event callback function where the system will changes
         * its behaviour or perform an action based on the event details
         * @param l_e details of the event
         */
        virtual void notify(const ObjectEventContext &l_e) override;
    };

}