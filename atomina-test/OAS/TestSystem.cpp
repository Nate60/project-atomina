#include "TestSystem.hpp"

TestSystem::TestSystem(): SysBase(0u)
{
    m_req.set(0);
}

void
TestSystem::notify(const ATMA::ObjectEventContext &l_e)
{
    for(auto &obj: m_objects)
    {
        std::shared_ptr<TestAttribute> attr = ctx.getAttribute<TestAttribute>(obj, 0u);
        attr->flag = true;
    }
}

void
TestSystem::update(const float &l_dt)
{
    if(m_enabled)
        for(auto &obj: m_objects)
        {
            std::shared_ptr<TestAttribute> attr = ctx.getAttribute<TestAttribute>(obj, 0u);
            attr->flag = true;
        }
}