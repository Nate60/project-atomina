#pragma once
#include "pch.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/System.hpp"
#include "OAS/attributes/AttrShape.hpp"
#include "OAS/attributes/AttrVelocity.hpp"
#include "OAS/Attribute.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * Implementation of system that handles the movement of
     * objects
     */
    class SysTranslator: public SysBase
    {
    public:
        // default constructor
        SysTranslator();

        // deconstructor
        virtual ~SysTranslator();

        /**
         * update internal members on an engine tick basis
         * @param l_dt the time since last update
         */
        void update(const long long &l_dt) override;

        /**
         * event callback function where the system will changes
         * its behaviour or perform an action based on the event details
         * @param l_e details of the event
         */
        virtual void notify(const ObjectEventContext &l_e) override;
    };

}