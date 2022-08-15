#include "EventTestSuite.hpp"

TEST_F(EventFixture, EventModifiesAttribute)
{
    ATMA::AttrTranslatable attr{};
    unsigned int obj = this->ctx.createObject();
    this->ctx.registerAttributeType<ATMA::AttrTranslatable>(
        ATMA::AttrType(ATMA::Attribute::Translatable)
    );
    this->ctx.addAttribute(obj, ATMA::AttrType(ATMA::Attribute::Translatable));
    auto clbck = [&](ATMA::EventContext &) -> void
    {
        auto &ctx = ATMA::ATMAContext::getContext();
        auto attr = ctx.getAttribute<ATMA::AttrTranslatable>(
            obj, ATMA::AttrType(ATMA::Attribute::Translatable)
        );
        attr->m_x = 100;
    };
    this->ctx.addCallback(0u, 0u, clbck);
    this->ctx.addEvent(0u, 0u, ATMA::EventContext{});
    this->ctx.update();
    auto outerAttr = ctx.getAttribute<ATMA::AttrTranslatable>(
        obj, ATMA::AttrType(ATMA::Attribute::Translatable)
    );
    EXPECT_EQ(100, outerAttr->m_x);
}

TEST_F(EventFixture, HandleEventWithNoCallback)
{
    this->ctx.addEvent(0u, 0u, ATMA::EventContext{});
    this->ctx.update();
    SUCCEED();
}