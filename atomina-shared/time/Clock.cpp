#include "pch.hpp"
#include "Clock.hpp"

namespace ATMA
{

    void Clock::start()
    {
        if(!m_started)
        {
            m_started = true;
            m_startTime = m_self.now();
        }
        else
        {
            throw TimeException("Cannot start started clock");
        }
    }

    bool Clock::isStarted()
    {
        return m_started;
    }

    void Clock::stop()
    {
        if(!m_stopped && m_started)
        {
            m_stopped = true;
            m_stopTime = m_self.now();
        }
        else
        {
            throw TimeException("Cannot stop clock that is not started, or stopped");
        }
    }

    bool Clock::isStopped()
    {
        return m_stopped;
    }

    const std::chrono::time_point<std::chrono::steady_clock> &Clock::getStartTime()
    {
        if(m_started)
            return m_startTime;
        else
            throw TimeException("Clock has not been started");
    }

    std::chrono::time_point<std::chrono::steady_clock> Clock::getCurrentTime()
    {
        if(m_stopped)
            return m_stopTime;
        else if(m_started)
            return m_self.now();
        else
            throw TimeException("Clock has not been started");
    }

    const std::chrono::time_point<std::chrono::steady_clock> &Clock::getStopTime()
    {
        if(m_stopped)
            return m_stopTime;
        else
            throw TimeException("Clock has not been stopped");
    }

}