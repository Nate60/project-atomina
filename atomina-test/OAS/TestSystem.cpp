#include "TestSystem.hpp"

TestSystem::TestSystem(): SysBase(0u, "Test")
{
    m_req.push_back(std::bitset<ATConst::BITSET_SIZE>{});
    m_req[0].set(0);
}

void TestSystem::notify(ATMA::ATMAContext *l_ctx, const ATMA::ObjectEventContext &l_e)
{
    for(auto &obj: m_objects)
    {
        std::shared_ptr<TestAttribute> attr = l_ctx->m_attrMan->getAttribute<TestAttribute>(obj.second, 0u);
        attr->flag = true;
    }
}

void TestSystem::update(ATMA::ATMAContext *l_ctx, const double &l_dt)
{
    if(m_enabled)
        for(auto &obj: m_objects)
        {
            std::shared_ptr<TestAttribute> attr = l_ctx->m_attrMan->getAttribute<TestAttribute>(obj.second, 0u);
            attr->flag = true;
        }
}
