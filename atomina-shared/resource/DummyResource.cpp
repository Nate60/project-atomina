#include "pch.hpp"
#include "DummyResource.hpp"

namespace ATMA
{

    DummyResource::DummyResource(const std::string &l_name): Resource(l_name) {}

    DummyResource::DummyResource(const std::string &l_name, const std::string &l_filename):
        Resource(l_name, l_filename)
    {
    }

    DummyResource::~DummyResource() {}
}