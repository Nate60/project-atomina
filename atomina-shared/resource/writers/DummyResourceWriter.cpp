#include "pch.hpp"
#include "DummyResourceWriter.hpp"

namespace ATMA
{
    ResourceWriter<DummyResource>::ResourceWriter() {}

    ResourceWriter<DummyResource>::~ResourceWriter() {}

    void ResourceWriter<DummyResource>::write(const std::shared_ptr<DummyResource> l_res, const Path &l_path) {}

}
