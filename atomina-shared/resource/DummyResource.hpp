#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "Resource.hpp"

namespace ATMA
{

    class ATMA_API DummyResource: public Resource
    {
    public:
        DummyResource(const std::string &l_name);

        DummyResource(const std::string &l_name, const std::string &l_filename);

        virtual ~DummyResource();
    };

    inline bool operator==(const DummyResource &a, const DummyResource &b);

}
