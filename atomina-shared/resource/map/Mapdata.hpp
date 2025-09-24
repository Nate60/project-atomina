#pragma once
#include "math/Vec2.hpp"
#include "pch.hpp"
#include "render/Transform.hpp"
#include "resource/Resource.hpp"

namespace ATMA
{

    class Mapdata: public LoadedResource
    {
    public:
        Mapdata(
            const std::vector<unsigned int> &l_data,
            const unsigned int &l_width,
            const Vec2<unsigned int> &l_tilesize = {32, 32}
        );
        virtual ~Mapdata();
        const unsigned int &width() const;
        const std::vector<unsigned int> &data() const;
        const Vec2<unsigned int> &tilesize() const;
    protected:
        unsigned int m_width;
        std::vector<unsigned int> m_data;
        Vec2<unsigned int> m_tilesize;
    };
}
