#include "TestSystem.hpp"

TestSystem::TestSystem(): SysBase(0u, "Test")
{
    m_req.push_back(std::bitset<ATConst::OBJECT_BIT_SIZE>{});
    m_req[0].set(0);
}

void
TestSystem::notify(const ATMA::ObjectEventContext &l_e)
{
    for(auto &obj: m_objects)
    {
        std::shared_ptr<TestAttribute> attr = ctx.getAttribute<TestAttribute>(obj.second, 0u);
        attr->flag = true;
    }
}

void
TestSystem::update(const long long &l_dt)
{
    if(m_enabled)
        for(auto &obj: m_objects)
        {
            std::shared_ptr<TestAttribute> attr = ctx.getAttribute<TestAttribute>(obj.second, 0u);
            attr->flag = true;
        }
}