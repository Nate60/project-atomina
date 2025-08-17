#pragma once
#include "AtominaTest.hpp"
#include "TestAttribute.hpp"
#include "core/ATMAContext.hpp"

/**
 * Dummy system for testing internals of ATMA Contexts
 * and implementations that require systems
 */
class TestSystem: public ATMA::SysBase
{
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
    virtual void update(ATMA::ATMAContext *l_ctx, const long long &l_dt) override;

    /**
     * Triggers any event specific functionality of the system
     * @param l_e event details of the passed event
     */
    virtual void notify(ATMA::ATMAContext *l_ctx, const ATMA::ObjectEventContext &l_e) override;
};
