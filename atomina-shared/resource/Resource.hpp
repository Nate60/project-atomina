#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include <memory>

namespace ATMA
{

    class ATMA_API Resource
    {
    public:
        Resource();
        Resource(const std::string &l_fileName);
        ~Resource();
    };

    inline bool operator==(const Resource &a, const Resource &b);

}