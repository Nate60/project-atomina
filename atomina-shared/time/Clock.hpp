#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/AtominaException.hpp"

namespace ATMA
{

    /**
     * Steady clock for keeping track has passed between
     * continuous time points
     */
    class Clock
    {
    public:
        /**
         * Starts the
         * @throws TimeException if clock is already started
         */
        void start();

        /**
         * setter for started flagged
         * @returns if timer has been started
         */
        bool isStarted();

        /**
         * Stops the clock
         * @throws TimeException if the clock is not started or is already stopped
         */
        void stop();

        /**
         * setter for stopped flagged
         * @returns if the timer has been stopped
         */
        bool isStopped();

        /**
         * getter for clock start timepoint
         * @returns timepoint of when clock started
         * @throws TimeException if Clock was not started
         */
        const std::chrono::time_point<std::chrono::steady_clock> &getStartTime();

        /**
         * getter for clocks current timepoint
         * @returns timepoint of clock
         * @throws TimeException if the clock has not been started
         */
        std::chrono::time_point<std::chrono::steady_clock> getCurrentTime();

        /**
         * getter for clock stop timepoint
         * @returns timepoint of when clock stopped
         * @throws TimeException if the clock has not been stopped
         */
        const std::chrono::time_point<std::chrono::steady_clock> &getStopTime();
    protected:
        bool m_started = false;
        bool m_stopped = false;
        std::chrono::steady_clock m_self{};
        std::chrono::time_point<std::chrono::steady_clock> m_startTime;
        std::chrono::time_point<std::chrono::steady_clock> m_stopTime;
    };

}