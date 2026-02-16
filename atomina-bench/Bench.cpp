#include "Bench.hpp"

void Result::arrange(const std::map<int, long long> &l_times)
{
    ATMA_ENGINE_INFO("---------------------------------------------------------------------");
    for(auto itr = l_times.begin(); itr != l_times.end(); itr++)
    {
        ATMA_ENGINE_INFO("{:4d}\t {:12.2f}ms", itr->first, itr->second / 1000000.0);
    }
    ATMA_ENGINE_INFO("---------------------------------------------------------------------");
}
