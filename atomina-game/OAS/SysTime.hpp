#pragma once
#include <atomina.hpp>
#include "../GameEnums.hpp"
#include "AttrTimer.hpp"
#include "core/ATMAContext.hpp"

class SysTime: public ATMA::SysBase
{
public:
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
    virtual void update(ATMA::ATMAContext &l_ctx, const long long &l_dt) override
    {
        if(!m_enabled)
            return;
        for(auto &objId: m_objects)
        {
            std::shared_ptr<AttrTimer> timerAttr =
                l_ctx.m_attrMan->getAttribute<AttrTimer>(objId.second, GameAttributeType(GameAttributeEnum::TIMER));
            if(timerAttr->m_clock.getElapsedDuration() > timerAttr->m_amount && !timerAttr->m_elapsed)
            {
                l_ctx.m_eventMan->dispatchObjectEvent(ATMA::ObjectEventContext{
                    GameEventType(GameEventEnum::TIMER_COMPLETE)});
                timerAttr->m_elapsed = true;
            }
        }
    }

    /**
     * event callback function where the system will changes
     * its behaviour or perform an action based on the event details
     * @param l_e details of the event
     */
    virtual void notify(const ATMA::ObjectEventContext &l_e) override {}

    std::unordered_map<std::optional<unsigned int>, unsigned int> m_conns{};
};
