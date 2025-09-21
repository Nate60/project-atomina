#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/ResourceWriter.hpp"
#include "resource/graphics/Animation.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    template<>
    class ResourceWriter<Animation>
    {
    public:
        ResourceWriter();
        virtual ~ResourceWriter();
        void write(const std::shared_ptr<Animation> l_res, const Path &l_path);
    };
}
