#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/ResourceLoader.hpp"
#include "resource/DummyResource.hpp"
#include "util/Path.hpp"

namespace ATMA
{
    template<>
    class ResourceLoader<DummyResource>
    {
    public:
        ResourceLoader();
        virtual ~ResourceLoader();
        std::shared_ptr<DummyResource> load(const std::string &l_name, const Path &l_path);
        std::shared_ptr<DummyResource> load(const std::string &l_name);
    };
}