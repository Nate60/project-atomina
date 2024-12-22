#pragma once
#include "AtominaTest.hpp"
#include "TestAttribute.hpp"

/**
 * Dummy system for testing internals of ATMA Contexts
 * and implementations that require systems
 */
class TestSystem: public ATMA::SysBase, public ATMA::NetworkMessageListener
{
private:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
public:
    /**
     * Default Constructor
     */
    TestSystem();

    /**
     * Updates all attributes contained in the systems with respect to
     * how many ticks have passed
     * @param l_dt time since last update
     */
    virtual void update(const long long &l_dt) override;

    /**
     * Triggers any event specific functionality of the system
     * @param l_e event details of the passed event
     */
    virtual void notify(const ATMA::ObjectEventContext &l_e) override;

    virtual void notify(const std::optional<const unsigned int> &l_id, const ATMA::NetworkMessage &l_msg) override;
};