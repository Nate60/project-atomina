#include "pch.hpp"
#include "Resource.hpp"

namespace ATMA
{
    Resource::Resource(const std::string &l_name): m_resourceName(l_name) {}

        // constructor with name and filename of resource
    Resource::Resource(const std::string &l_name, const Path &l_path): m_resourceName(l_name) {}

    Resource::~Resource() {}

}