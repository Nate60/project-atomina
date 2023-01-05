#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/attributes/AttrGraphic.hpp"
#include "OAS/attributes/AttrAnimation.hpp"
#include "OAS/System.hpp"

namespace ATMA
{

    /**
     * System implemenation that handles updating animations of objects 
     */
    class ATMA_API SysAnimator: public SysBase
    {
    public:

        //default constructor
        SysAnimator();

        //deconstructor
        ~SysAnimator();
  
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