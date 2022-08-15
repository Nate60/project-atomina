#pragma once
#include "../AtominaTest.hpp"
#include "TestAttribute.hpp"
#include "event/EventContext.hpp"

class TestSystem : public ATMA::SysBase
{
public:

    TestSystem();

    void doSomething(ATMA::EventContext &ectx);

    virtual void update(const float &l_dt) override;

};