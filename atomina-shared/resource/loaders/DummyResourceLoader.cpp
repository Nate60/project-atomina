#include "pch.hpp"
#include "DummyResourceLoader.hpp"

namespace ATMA
{

    ResourceLoader<DummyResource>::ResourceLoader() {}

    ResourceLoader<DummyResource>::~ResourceLoader() {}

    std::shared_ptr<DummyResource> ResourceLoader<DummyResource>::load(const std::string &l_name, const Path &l_path)
    {
        return std::make_shared<DummyResource>(l_name, l_path);
    }

    std::shared_ptr<DummyResource> ResourceLoader<DummyResource>::load(const std::string &l_name)
    {
        return std::make_shared<DummyResource>(l_name, Path{""});
    }
}