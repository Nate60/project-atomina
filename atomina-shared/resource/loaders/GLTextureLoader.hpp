#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/ResourceLoader.hpp"
#include "render/GLTexture.hpp"

namespace ATMA
{
    template<>
    class ResourceLoader<GLTexture>
    {
    public:
        ResourceLoader();
        virtual ~ResourceLoader();
        std::shared_ptr<GLTexture> load(const std::string &l_name, const Path &l_path);
        std::shared_ptr<GLTexture> load(const std::string &l_name);
    };
}