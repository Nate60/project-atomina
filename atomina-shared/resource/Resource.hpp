#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Path.hpp"

namespace ATMA
{
    struct Resource
    {
    public:
        Resource(const std::string &l_name, const Path &l_path, const unsigned int &l_type);
        virtual ~Resource();
        const std::string m_name;
        const Path m_path;
        const unsigned int m_type;
    };

    struct LoadedResource
    {
    };
}