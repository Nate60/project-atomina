#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLShader.hpp"
#include "resource/ResourceWriter.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    template<>
    class ResourceWriter<GLShader>
    {
    public:
        ResourceWriter();
        virtual ~ResourceWriter();
        void write(const std::shared_ptr<GLShader> l_res, const Path &l_path);
    };
}
