#pragma once
#include "pch.hpp"
#include "resource/ResourceWriter.hpp"
#include "resource/graphics/Tileset.hpp"

namespace ATMA
{
    template<>
    class ResourceWriter<Tileset>
    {
    public:
        ResourceWriter();
        virtual ~ResourceWriter();

        void write(const std::shared_ptr<Tileset> l_res, const Path &l_path);
    };
}
