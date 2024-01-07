#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "Resource.hpp"

namespace ATMA
{

    /**
     * Dummy Implementation of Resource
     */
    class ATMA_API DummyResource: public Resource
    {
    public:
        // constructor specifying resource name
        DummyResource(const std::string &l_name);

        // constructor specifying resource name and filepath
        DummyResource(const std::string &l_name, const std::string &l_filename);

        // default deconstructor
        virtual ~DummyResource();
    };

    // equality comparison operator
    inline bool operator==(const DummyResource &a, const DummyResource &b);

}
