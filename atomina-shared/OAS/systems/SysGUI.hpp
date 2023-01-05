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

    /**
     * System implementation that handles objects with graphical
     * use interface components 
     */
    class ATMA_API SysGUI: public SysBase
    {
    public:
    
    //default constructor
        SysGUI();

    //deconstructor
        ~SysGUI();

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