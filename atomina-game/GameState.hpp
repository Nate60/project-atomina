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

class GameState: public ATMA::BaseState
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    GameState(): BaseState() {}

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

    virtual void onDestroy() override {}

    virtual void activate() override {}

    virtual void deactivate() override {}

    virtual unsigned int getId() const override
    {
        return ATMA::StateType(ATMA::State::COUNT);
    }

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

    virtual void update(const sf::Time &l_time) override {}

    virtual void draw() override {}
};