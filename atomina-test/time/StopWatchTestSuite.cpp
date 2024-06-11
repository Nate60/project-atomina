#include "StopWatchTestSuite.hpp"

/**
 * Cannot stop a Stopwatch that has not been started
 */
TEST(StopWatchSuite, StoppingNonStarted)
{
    ATMA::StopWatch t{};
    EXPECT_THROW(t.stop(), ATMA::TimeException);
}

/**
 * Cannot stop a Stopwatch that has already been stopped
 */
TEST(StopWatchSuite, StoppingStopped)
{
    ATMA::StopWatch t{};
    t.start();
    t.stop();
    EXPECT_THROW(t.stop(), ATMA::TimeException);
}

/**
 * Cannot start a stopped stopwatch
 */
TEST(StopWatchSuite, StartingStopped)
{
    ATMA::StopWatch t{};
    t.start();
    t.stop();
    EXPECT_THROW(t.start(), ATMA::TimeException);
}

/**
 * Cannot start a stopwatch that has already been started
 */
TEST(StopWatchSuite, StartingStarted)
{
    ATMA::StopWatch t{};
    t.start();
    EXPECT_THROW(t.start(), ATMA::TimeException);
}

/**
 * Cannot pause a stopwatch that has not been started
 */
TEST(StopWatchSuite, PausingNonStarted)
{
    ATMA::StopWatch t{};
    EXPECT_THROW(t.pause(), ATMA::TimeException);
}

/**
 * Cannot pause a stopwatch that has already been paused
 */
TEST(StopWatchSuite, PausingPaused)
{
    ATMA::StopWatch t{};
    t.start();
    t.pause();
    EXPECT_THROW(t.pause(), ATMA::TimeException);
}

/**
 * Cannot pause a stopped stopwatch
 */
TEST(StopWatchSuite, PausingStopped)
{
    ATMA::StopWatch t{};
    t.start();
    t.stop();
    EXPECT_THROW(t.pause(), ATMA::TimeException);
}

/**
 * Cannot unpause a stopwatch that is not paused
 */
TEST(StopWatchSuite, UnpausingUnpaused)
{
    ATMA::StopWatch t{};
    EXPECT_THROW(t.unpause(), ATMA::TimeException);
}

/**
 * Cannot unpaused a stopped stopwatch
 */
TEST(StopWatchSuite, UnpausedStopped)
{
    ATMA::StopWatch t{};
    t.start();
    t.pause();
    t.stop();
    EXPECT_THROW(t.unpause(), ATMA::TimeException);
}

/**
 * Cannot get elapsed duration of a stopwatch that has not been started
 */
TEST(StopWatchSuite, GetElapsedNonStart)
{
    ATMA::StopWatch t{};
    EXPECT_THROW(t.getElapsedDuration(), ATMA::TimeException);
}

/**
 * Starting stopwatch sets its flag
 */
TEST(StopWatchSuite, Start)
{
    ATMA::StopWatch t{};
    t.start();
    EXPECT_TRUE(t.isStarted());
}

/**
 * StopWatch start flag starts false
 */
TEST(StopWatchSuite, NonStart)
{
    ATMA::StopWatch t{};
    EXPECT_FALSE(t.isStarted());
}

/**
 * StopWatch stop flag starts false
 */
TEST(StopWatchSuite, NonStop)
{
    ATMA::StopWatch t{};
    t.start();
    EXPECT_FALSE(t.isStopped());
}

/**
 * Stopping stopwatch sets its flag
 */
TEST(StopWatchSuite, Stop)
{
    ATMA::StopWatch t{};
    t.start();
    t.stop();
    EXPECT_TRUE(t.isStopped());
}

 /**
  * Pausing sets stopwatch pause flag
  */
TEST(StopWatchSuite, Pause)
{
    ATMA::StopWatch t{};
    t.start();
    t.pause();
    EXPECT_TRUE(t.isPaused());
}

/**
 * Pausing flag starts false
 */
TEST(StopWatchSuite, NonPause)
{
    ATMA::StopWatch t{};
    t.start();
    EXPECT_FALSE(t.isPaused());
}

/**
 * Unpausing a paused stopwatch will switch off
 * paused flag
 */
TEST(StopWatchSuite, UnpausePaused)
{
    ATMA::StopWatch t{};
    t.start();
    t.pause();
    t.unpause();
    EXPECT_FALSE(t.isPaused());
}

/**
 * Reset will reset flag state of StopWatch
 */
TEST(StopWatchSuite, ResetPaused)
{
    ATMA::StopWatch t{};
    t.start();
    t.pause();
    t.stop();
    t.reset();
    EXPECT_FALSE(t.isStarted());
    EXPECT_FALSE(t.isPaused());
    EXPECT_FALSE(t.isStopped());
}

/**
 * Reset will reset elapsed duration
 */
TEST(StopWatchSuite, ResetDuration)
{
    ATMA::StopWatch t1{};
    ATMA::StopWatch t2{};
    t1.start();
    t2.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    t1.reset();
    t1.start();
    EXPECT_NE(t1.getElapsedDuration(), t2.getElapsedDuration());
}

/**
 * Elapsed time will not change once the stopwatch is stopped
 */
TEST(StopWatchSuite, ElapsedTimeIsStopped)
{
    ATMA::StopWatch t{};
    t.start();
    t.stop();
    auto firstTime = t.getElapsedDuration();
    auto secondTime = t.getElapsedDuration();
    EXPECT_EQ(firstTime,secondTime);
}
