#pragma once
#include "AtominaTest.hpp"

template<class T>
class AttributeFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
    void addAttribute(const unsigned int &l_obj, T &attr)
    {
        ctx.registerAttributeType<T>(attr.getType());
        ctx.addAttribute(l_obj, attr.getType());
    }

    void removeAttribute(const unsigned int &l_obj, T &attr)
    {
        ctx.removeAttribute(l_obj, attr.getType());
    }

    std::shared_ptr<T> getAttribute(const unsigned int &l_obj, T &l_attr)
    {
        return ctx.getAttribute<T>(l_obj, l_attr.getType());
    }

    void TearDown() override
    {
        auto &ctx = ATMA::ATMAContext::getContext();
        ctx.purge();
    }
};

class UntypedAttributeFixture: public ::testing::Test
{
protected:
    void TearDown() override
    {
        auto &ctx = ATMA::ATMAContext::getContext();
        ctx.purge();
    }
};