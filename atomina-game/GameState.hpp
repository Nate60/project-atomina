#pragma once
#include "OAS/Attribute.hpp"
#include "OAS/attributes/AttrMouseRegion.hpp"
#include "OAS/attributes/AttrMouseTrigger.hpp"
#include "event/ObjectEvent.hpp"
#include "event/ObjectEventContext.hpp"
#include "util/Log.hpp"
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <atomina.hpp>

/**
 * Game Implementation of state to implement a user defined extended state
 * that is external to the engine
 */
class GameState: public ATMA::BaseState
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    //default constructor
    GameState(): BaseState() {}

    /**
     * Game app implementation of onCreate function to be the initialization
     * of the game app user defined objects
     */
    virtual void onCreate() override
    {
        // create button
        auto butID = ctx.createObject();
        ctx.addAttribute(butID, ATMA::AttributeType(ATMA::Attribute::MouseRegion));

        auto region = ctx.getAttribute<ATMA::AttrMouseRegion>(
            butID, ATMA::AttributeType(ATMA::Attribute::MouseRegion)
        );
        region->m_region.height = 100;
        region->m_region.width = 100;
        ctx.addAttribute(butID, ATMA::AttributeType(ATMA::Attribute::MouseTrigger));

        auto trigger = ctx.getAttribute<ATMA::AttrMouseTrigger>(
            butID, ATMA::AttributeType(ATMA::Attribute::MouseTrigger)
        );
        trigger->m_mouseReleaseFunc = [](const ATMA::ObjectEventContext &l_e) -> void
        { ATMA_ENGINE_INFO("Button was PRESSED!!"); };

        ctx.addAttribute(butID, ATMA::AttributeType(ATMA::Attribute::Graphic));
    }

    /**
     * stub implementation of onDestroy 
     */
    virtual void onDestroy() override {}

    /**
     * stub implementation of activate function
     */
    virtual void activate() override {}


    /**
     * stub implementation of deactive function 
     */
    virtual void deactivate() override {}

    /**
     * gets state id
     * @returns state id 
     */
    virtual unsigned int getId() const override
    {
        return ATMA::StateType(ATMA::State::COUNT);
    }

    /**
     * handle user input event passed from window
     * @param l_e user input event from window 
     */
    virtual void handleEvent(const ATMA::WindowEvent &l_e) override
    {
        sf::Event e = l_e.m_event;
        if(e.type == sf::Event::Closed)
        {
            ctx.dispatchObjectEvent(ATMA::ObjectEventContext{
                ATMA::ObjectEventType(ATMA::ObjectEvent::ShutDown)});
        }
        else if(e.type == sf::Event::MouseButtonReleased)
        {
            ATMA::Props eventProps{};
            eventProps["mousepos"] =
                sf::Vector2i{l_e.m_event.mouseButton.x, l_e.m_event.mouseButton.y};
            ctx.dispatchObjectEvent(ATMA::ObjectEventContext{
                ATMA::ObjectEventType(ATMA::ObjectEvent::MouseReleased), eventProps});
        }
    }

    /**
     * stub implemenation of update
     * @param l_time time passed since update 
     */
    virtual void update(const sf::Time &l_time) override {}

    /**
     * stub implemenation of draw 
     */
    virtual void draw() override {}
};