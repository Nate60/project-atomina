#include "TestSystem.hpp"

TestSystem::TestSystem(): SysBase(0u)
{
    m_req.set(0);
}

void
TestSystem::doSomething(ATMA::EventContext &ectx)
{
    throw ATMA::ValueNotFoundException("test exception");
}

void
TestSystem::update(const float &l_dt)
{
    if(m_enabled)
        for(auto &obj: m_objects)
        {
            std::shared_ptr<TestAttribute> attr =
                ATMA::ATMAContext::getContext().getAttribute<TestAttribute>(obj, 0u);
            attr->flag = true;
        }
}