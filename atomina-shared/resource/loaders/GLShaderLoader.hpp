#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/ResourceLoader.hpp"
#include "render/GLShader.hpp"

namespace ATMA
{
    template<>
    class ResourceLoader<GLShader>
    {
    public:
        ResourceLoader();
        virtual ~ResourceLoader();
        std::shared_ptr<GLShader> load(const std::string &l_name, const Path &l_path);
        std::shared_ptr<GLShader> load(const std::string &l_name);
    };
}