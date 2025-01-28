#pragma once
#include <atomina.hpp>
#include "../GameEnums.hpp"
#include "AttrTimer.hpp"

class SysTime: public ATMA::SysBase
{
public:
    ATMA::ATMAContext &ctx = ctx.getContext();
    // default constructor
    SysTime(): SysBase(GameSystemType(GameSystemEnum::TIME), "Time") 
    {
        auto &ctx = ATMA::ATMAContext::getContext();
        m_req.push_back(std::bitset<ATConst::OBJECT_BIT_SIZE>{});
        m_req[0].set(GameAttributeType(GameAttributeEnum::TIMER));
    }

    // deconstructor
    virtual ~SysTime() {}

    /**
    * update internal members on an engine tick basis
    * @param l_dt the time since last update
    */
    virtual void update(const long long &l_dt) override
    {
        if(!m_enabled)
            return;
        for(auto &objId : m_objects)
        {
            std::shared_ptr<AttrTimer> timerAttr = ctx.getAttribute<AttrTimer>(objId.second, GameAttributeType(GameAttributeEnum::TIMER));
            if(timerAttr->m_clock.getElapsedDuration() > timerAttr->m_amount && !timerAttr->m_elapsed)
            {
                ctx.dispatchObjectEvent(ATMA::ObjectEventContext{GameEventType(GameEventEnum::TIMER_COMPLETE)});
                timerAttr->m_elapsed = true;
            }
        }
    }

    /**
    * event callback function where the system will changes
    * its behaviour or perform an action based on the event details
    * @param l_e details of the event
    */
    virtual void notify(const ATMA::ObjectEventContext &l_e) override
    {}

    std::unordered_map<std::optional<unsigned int>, unsigned int> m_conns{};
};