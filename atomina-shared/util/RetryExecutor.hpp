#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * interface for running tasks asynchronously
     */
    class ATMA_API RetryExecutor
    {
    public:
        /**
         * checks if the assigned task has been completed
         * @returns task is completed
         */
        bool isDone() const;

        /**
         * checks if the task has been started
         * @returns task has started
         */
        bool isSuccessful() const;

        static RetryExecutor
        withRetries(const unsigned int &l_count, const std::function<void(void)> &l_func);
    private:
        void tryExec(const unsigned int &l_count, const std::function<void(void)> &l_func)
        {

            for(unsigned int i = 0; i < l_count; i++)
            {
                try
                {
                    l_func();
                }
                catch(...)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(60));
                    continue;
                }
                m_done = true;
                m_success = true;
                return;
            }
            m_done = true;
            m_success = false;
        }

        RetryExecutor(const unsigned int &l_count, const std::function<void(void)> &l_func):
            m_done(false),
            m_success(false)
        {
            tryExec(l_count, l_func);
        }

        bool m_done;
        bool m_success;
    };

}
