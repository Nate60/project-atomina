#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLTexture.hpp"
#include "resource/ResourceWriter.hpp"
#include "util/AtominaException.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    template<>
    class ResourceWriter<GLTexture>
    {
    public:
        ResourceWriter();
        virtual ~ResourceWriter();

        // TODO: A-145
        void write(const std::shared_ptr<GLTexture> l_res, const Path &l_path)
        {
            throw SerializationException("Texture Writing not supported");
        }
    };
}
