#include "pch.hpp"
#include "DummyResource.hpp"

namespace ATMA
{

    DummyResource::DummyResource(const std::string &l_name, const Path &l_path):
        Resource(l_name, l_path, 0u),
        LoadedResource()
    {
    }

    DummyResource::~DummyResource() {}
}