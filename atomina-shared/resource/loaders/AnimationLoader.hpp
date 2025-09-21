#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/ResourceLoader.hpp"
#include "resource/graphics/Animation.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    template<>
    class ResourceLoader<Animation>
    {
    public:
        ResourceLoader();
        virtual ~ResourceLoader();
        std::shared_ptr<Animation> load(const std::string &l_name, const Path &l_path);
        std::shared_ptr<Animation> load(const std::string &l_name);
    };
}
