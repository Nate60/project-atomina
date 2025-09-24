#include "pch.hpp"
#include "DummyResource.hpp"

namespace ATMA
{

    DummyResource::DummyResource(const std::string &l_name, const Path &l_path):
        LoadedResource(),
        Resource(l_name, l_path, 0u)
    {
    }

    DummyResource::~DummyResource() {}
}
