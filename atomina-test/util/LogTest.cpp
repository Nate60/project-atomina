#include "LogTest.hpp"

using namespace std::string_literals;

/**
 * Given an attribute the logger should print its type name
 */
TEST_F(LogFixture, LoggingAttributeGivesName)
{
    std::shared_ptr<ATMA::AttrBase> attr = std::make_shared<ATMA::AttrPosition>(ATMA::AttrPosition{});
    testLogger->info("{}", attr);
    EXPECT_EQ("Position"s + LogFixture::endLine, oss.str());
}

/**
 * Given a system the logger should print its type name
 */
TEST_F(LogFixture, LoggingSystemGivesName)
{
    std::shared_ptr<ATMA::SysBase> sys = std::make_shared<ATMA::SysTranslator>(ATMA::SysTranslator{});
    testLogger->info("{}", sys);
    EXPECT_EQ("Translator"s  + LogFixture::endLine, oss.str());
}

/**
 * Given a resource the logger should print its type name
 */
TEST_F(LogFixture, LoggingResourceGivesName)
{
    std::shared_ptr<ATMA::Resource> res = std::make_shared<ATMA::DummyResource>(ATMA::DummyResource{"some resource"});
    testLogger->info("{}", res);
    EXPECT_EQ("some resource"s + LogFixture::endLine, oss.str());
}

/**
 * Given an event the logger should print its name property
 */
TEST_F(LogFixture, LoggingEventGivesName)
{
    ATMA::Props p{};
    p["name"] = "event"s;
    ATMA::ObjectEventContext e{0, p};
    testLogger->info("{}", e);
    EXPECT_EQ("event" + LogFixture::endLine, oss.str());
}

/**
 * Given an event with no name should print "[null]"
 */
TEST_F(LogFixture, LoggingEventWithNoNameGivesNull)
{
    ATMA::ObjectEventContext e{0, ATMA::Props{}};
    testLogger->info("{}", e);
    EXPECT_EQ("[null]"s  + LogFixture::endLine, oss.str());
}
