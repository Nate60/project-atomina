#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * interface for running tasks asynchronously
     */
    class ATMA_API Worker
    {
    public:
        Worker();

        /**
         * checks if the assigned task has been completed
         * @returns task is completed
         */
        bool isDone() const;

        /**
         * checks if the task has been started
         * @returns task has started
         */
        bool hasStarted() const;
    protected:
        /**
         * should implement the task handled by subclass
         */
        virtual void work() = 0;

        std::future<void> m_future = std::async(&Worker::work, this);
        std::mutex m_mtx;
        std::atomic<bool> m_started;
    };

}
