#pragma once
#include "AtominaTest.hpp"
#include "NetworkAttribute.hpp"

/**
 * Dummy system for testing internals of ATMA Contexts
 * and implementations that require systems
 */
class NetworkSystem: public ATMA::SysBase, public ATMA::NetworkMessageListener
{
private:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
public:
    /**
     * Default Constructor
     */
    NetworkSystem(): SysBase(0u, "network")
    {
        m_req.push_back(std::bitset<ATConst::OBJECT_BIT_SIZE>{});
        m_req[0].set(0);
    }

    /**
     * Updates all attributes contained in the systems with respect to
     * how many ticks have passed
     * @param l_dt time since last update
     */
    virtual void update(const long long &l_dt) override {}

    /**
     * Triggers any event specific functionality of the system
     * @param l_e event details of the passed event
     */
    virtual void notify(const ATMA::ObjectEventContext &l_e) override {}

    /**
     * pass the event details to the object to be handled
     * @param l_e event details
     */
    virtual void notify(const std::optional<const unsigned int> &l_id, const ATMA::NetworkMessage &l_e) override
    {
        if(m_enabled)
            for(auto &obj: m_objects)
            {
                std::shared_ptr<NetworkAttribute> attr = ctx.getAttribute<NetworkAttribute>(obj.second, 0u);
                attr->m_connId = l_id;
                if(auto itr = attr->m_resps.find(l_e.type()); itr != attr->m_resps.end())
                {
                    itr->second = l_e.values();
                }
                else
                {
                    attr->m_resps[l_e.type()] = l_e.values();
                }
            }
    }
};