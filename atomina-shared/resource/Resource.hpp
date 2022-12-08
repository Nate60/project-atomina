#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include <memory>

namespace ATMA
{

    class ATMA_API Resource
    {
    public:
    const std::string m_resourceName;
        Resource(const std::string &l_name);
        Resource(const std::string &l_name, const std::string &l_fileName);
        ~Resource();
    };

    inline bool operator==(const Resource &a, const Resource &b);

}