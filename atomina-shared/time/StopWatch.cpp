#include "pch.hpp"
#include "StopWatch.hpp"

namespace ATMA
{

    void StopWatch::start()
    {
        m_clock.start();
    }

    bool StopWatch::isStarted()
    {
        return m_clock.isStarted();
    }

    void StopWatch::stop()
    {
        m_clock.stop();
    }

    bool StopWatch::isStopped()
    {
        return m_clock.isStopped();
    }

    void StopWatch::pause()
    {
        if(!m_paused && m_clock.isStarted() && !m_clock.isStopped())
        {
            m_lastPauseTime = m_clock.getCurrentTime();
            m_paused = true;
        }
        else
        {
            throw TimeException("Cannot pause a paused, stopped, or not started stopwatch");
        }
    }

    void StopWatch::unpause() 
    {
        if(m_paused && !m_clock.isStopped())
        {
            auto endTimePoint = m_clock.getCurrentTime();
            m_pausedDuration += (endTimePoint - m_lastPauseTime).count();
            m_paused = false;
        }
        else
        {
            throw TimeException("Cannot unpause an unpaused, or stopped stopwatch");
        }
    }

    bool StopWatch::isPaused()
    {
        return m_paused;
    }

    void StopWatch::reset()
    {
        m_paused = false;
        m_pausedDuration = 0L;
        m_clock = Clock{};
    }

    long long StopWatch::getElapsedDuration()
    {
        auto now = m_clock.getCurrentTime();
        auto timeDelta = (now - m_clock.getStartTime());
        return (timeDelta.count() - m_pausedDuration);
    }

}