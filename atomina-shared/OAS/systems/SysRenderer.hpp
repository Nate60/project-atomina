#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/attributes/AttrGraphic.hpp"
#include "OAS/System.hpp"

namespace ATMA
{

    /**
     * Implementation of system that performs the rendering of 
     * objects
     */
    class ATMA_API SysRenderer: public SysBase, public sf::Drawable
    {
    public:
        //default constructor
        SysRenderer();

        //deconstructor
        ~SysRenderer();

        /**
         * updates the system internals according to engine ticks
         * @param l_dt the amount of time that has passed 
         */
        virtual void update(const float &l_dt) override;

        /**
         * draws objects registered to this system to the given render target
         * @param l_target the render target to draw the objects to
         * @param l_states the set of render states for the render target
         */
        virtual void draw(
            sf::RenderTarget &l_target,
            const sf::RenderStates &l_states = sf::RenderStates::Default
        ) const override;

        /**
         * callback notifies the system of an event occuring
         * @param l_e event details
         */
        virtual void notify(const ObjectEventContext &l_e) override;
    };

}