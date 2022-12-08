#pragma once
#include "AtominaTest.hpp"
#include <exception>
#include <memory>
#include <stdexcept>

using namespace std::string_literals;

/**
 * Fixture that implements its own logger that is dumped
 * to a string stream so that we can evaluate the results
 */
class LogFixture: public ::testing::Test
{
public:
#ifdef _WINDOWS
    static const inline std::string endLine = "\r\n"s;
#else
    static const inline std::string endLine = "\n"s;
#endif
protected:
    std::shared_ptr<spdlog::logger> testLogger;
    std::ostringstream oss;

    /**
     * Creates the logger and links it to the output string
     * stream
     */
    void SetUp() override
    {
        auto ostream_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(oss);
        testLogger = std::make_shared<spdlog::logger>("test_logger", ostream_sink);
        testLogger->set_pattern("%v");
        testLogger->set_error_handler([](const std::string &msg) { throw std::runtime_error(msg); }
        );
    }

    /**
     * Clears the logger state and clears the string stream
     * so no data is left over between tests
     */
    void TearDown() override
    {
        oss.clear();
        testLogger.reset();
    }
};