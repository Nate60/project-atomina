#include "ClockTestSuite.hpp"

/**
 * Cannot stop a clock that has not been started
 */
TEST(ClockSuite, StoppingNonStarted)
{
    ATMA::Clock t{};
    EXPECT_THROW(t.stop(), ATMA::TimeException);
}

/**
 * Cannot stop a clock that has already been stopped
 */
TEST(ClockSuite, StoppingStopped)
{
    ATMA::Clock t{};
    t.start();
    t.stop();
    EXPECT_THROW(t.stop(), ATMA::TimeException);
}

/**
 * Cannot start a stopped clock
 */
TEST(ClockSuite, StartingStopped)
{
    ATMA::Clock t{};
    t.start();
    t.stop();
    EXPECT_THROW(t.start(), ATMA::TimeException);
}

/**
 * Cannot start a clock that has already been started
 */
TEST(ClockSuite, StartingStarted)
{
    ATMA::Clock t{};
    t.start();
    EXPECT_THROW(t.start(), ATMA::TimeException);
}

/**
 * Cannot get start time of a clock that has not been started
 */
TEST(ClockSuite, GetStartNonStart)
{
    ATMA::Clock t{};
    EXPECT_THROW(t.getStartTime(), ATMA::TimeException);
}

TEST(ClockSuite, GetCurrentNonStart)
{
    ATMA::Clock t{};
    EXPECT_THROW(t.getCurrentTime(), ATMA::TimeException);
}

/**
 * Cannot get stop time of a clock that has not been stopped
 */
TEST(ClockSuite, GetStopNonStopped)
{
    ATMA::Clock t{};
    t.start();
    EXPECT_THROW(t.getStopTime(), ATMA::TimeException);
}

/**
 * Starting clock sets its flag
 */
TEST(ClockSuite, Start)
{
    ATMA::Clock t{};
    t.start();
    EXPECT_TRUE(t.isStarted());
}

/**
 * Clock start flag starts false
 */
TEST(ClockSuite, NonStart)
{
    ATMA::Clock t{};
    EXPECT_FALSE(t.isStarted());
}

/**
 * Clock stop flag starts false
 */
TEST(ClockSuite, NonStop)
{
    ATMA::Clock t{};
    t.start();
    EXPECT_FALSE(t.isStopped());
}

/**
 * Stopping clock sets its flag
 */
TEST(ClockSuite, Stop)
{
    ATMA::Clock t{};
    t.start();
    t.stop();
    EXPECT_TRUE(t.isStopped());
}

/**
 * Get Current Time gets stopped time if Clock is stopped
 */
TEST(ClockSuite, CurrentTimeIsStopped)
{
    ATMA::Clock t{};
    t.start();
    t.stop();
    EXPECT_EQ(t.getCurrentTime(), t.getStopTime());
}
