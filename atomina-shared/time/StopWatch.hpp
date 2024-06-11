#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "Clock.hpp"
#include "util/AtominaException.hpp"

namespace ATMA
{
    /**
     * Keeps track of the duration elapsed between
     * non-continuous timepoints
     */
    class ATMA_API StopWatch
    {
    public:
        /**
         * Starts the stopwatch
         * @throws TimeException if the stop watch has already been started
         */
        void start();

        /**
         * getter for started flagged
         * @returns if timer has been started
         */
        bool isStarted();

        /**
         * pauses the stopwatch 
         * @throws TimeException if the stop watch is already paused, stopped, or not
         * started
         */
        void pause();

        /**
         * unpauses the stopwatch
         * @throws TimeException if the stop watch is not paused or is stopped
         */
        void unpause();

        /**
         * getter for paused flag
         * @returns if the stop watch is paused
         */
        bool isPaused();

        /**
         * Stops the stopwatch
         * @throws TimeException if the stopwatch is not started or is already stopped
         */
        void stop();

        /**
         * setter for stopped flagged
         * @returns if the timer has been stopped
         */
        bool isStopped();

        /**
         * resets the state of the stop watch to not paused, not started, and not stopped
         * and the stopwatch's elaspsed duration
         */
        void reset();

        /**
         * Gives the duration from the current timepoint of the stopwatch excluding 
         * any time that it was paused
         * @returns non-continuous duration in nanoseconds between its start and current timepoints.
         * if the stopwatch is stopped it will give the duration between its start and stop instead
         * @throws TimeException if the stopwatch has not been started
         */
        long long getElapsedDuration();

    protected:
        Clock m_clock{};
        bool m_paused{false};
        long long m_pausedDuration{0L};        
        std::chrono::time_point<std::chrono::steady_clock> m_lastPauseTime;

    };
}