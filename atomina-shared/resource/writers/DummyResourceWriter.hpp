#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/DummyResource.hpp"
#include "resource/ResourceWriter.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    template<>
    class ResourceWriter<DummyResource>
    {
    public:
        ResourceWriter();
        virtual ~ResourceWriter();
        void write(const std::shared_ptr<DummyResource> l_res, const Path &l_path);
    };
}
