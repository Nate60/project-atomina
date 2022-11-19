#pragma once
#include "AtominaTest.hpp"
#include "TestAttribute.hpp"
#include "event/ObjectEventContext.hpp"

class TestSystem: public ATMA::SysBase
{
private:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
public:
    TestSystem();

    virtual void update(const float &l_dt) override;

    virtual void notify(const ATMA::ObjectEventContext &l_e) override;
};