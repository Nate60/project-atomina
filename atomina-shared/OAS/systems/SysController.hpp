#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/attributes/AttrPosition.hpp"
#include "OAS/System.hpp"

namespace ATMA
{
    /**
     * System that implements input control for objects allows for user inputs
     * to affect objects 
     */
    class ATMA_API SysController: public SysBase
    {
    public:

        //default constructor
        SysController();

        //deconstructor
        ~SysController();

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
