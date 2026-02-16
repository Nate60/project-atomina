#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/System.hpp"
#include "core/ATMAContext.hpp"
#include "render/Transform.hpp"

namespace ATMA
{
    /**
     * System that implements render calls on all objects that can be rendered
     */
    class SysRenderer: public SysBase
    {
    public:
        // default constructor
        SysRenderer();

        // deconstructor
        virtual ~SysRenderer();

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

        /**
         * adds object to the system
         * @param l_id id of the object
         * @returns if the operation was successful
         */
        virtual bool addObject(ATMAContext *l_ctx, const ObjectId &l_id, const unsigned int &l_patternID = 0u) override;

        /**
         * removes object from the system
         * @param l_id id of the object
         * @returns if the operation was successful
         */
        virtual bool removeObject(ATMAContext *l_ctx, const ObjectId &l_id) override;
    };

}
