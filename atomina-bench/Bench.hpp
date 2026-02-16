#pragma once
#include <atomina.hpp>

struct Result
{
    static void arrange(const std::map<int, long long> &l_times);
};

template<class T>
class Benchmark
{
public:
    Benchmark(const std::function<void(const T &)> &l_func, const std::map<int, T> &l_values)
    {
        std::map<int, long long> times{};
        for(auto itr = l_values.begin(); itr != l_values.end(); itr++)
        {
            ATMA::StopWatch watch{};
            watch.start();
            l_func(itr->second);
            watch.stop();
            times[itr->first] = watch.getElapsedDuration();
        }
        Result::arrange(times);
    }

    virtual ~Benchmark() {}
};
