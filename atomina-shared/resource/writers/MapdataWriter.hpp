#pragma once
#include "resource/ResourceWriter.hpp"
#include "resource/map/Mapdata.hpp"

namespace ATMA
{
    template<>
    class ResourceWriter<Mapdata>
    {
    public:
        ResourceWriter();
        virtual ~ResourceWriter();

        void write(const std::shared_ptr<Mapdata> l_res, const Path &l_path);
    };
}
