#include "TestSystem.hpp"

TestSystem::TestSystem(): SysBase(0u, "Test")
{
    std::bitset<ATConst::OBJECT_BIT_SIZE> first{};

    first.set(0);

    m_req.push_back(first);
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