#include "pch.hpp"
#include "RetryExecutor.hpp"

namespace ATMA
{

    bool RetryExecutor::isDone() const
    {
        return m_done;
    }

    bool RetryExecutor::isSuccessful() const
    {
        return m_success;
    }

    RetryExecutor
    RetryExecutor::withRetries(const unsigned int &l_count, const std::function<void(void)> &l_func)
    {
        return RetryExecutor(l_count, l_func);
    }

}