#pragma once
#include "pch.hpp"
#include "resource/graphics/Tileset.hpp"
#include "resource/map/Mapdata.hpp"
#include "Renderable.hpp"

namespace ATMA
{

    struct TilemapData
    {
        std::shared_ptr<Tileset> m_set;
        std::shared_ptr<Mapdata> m_map;
        Vec2<float> m_pos;
        unsigned int m_sheetWidth;
    };

    class Tilemap: public Renderable
    {
    public:
        Tilemap();
        Tilemap(const TilemapData &l_data);
        virtual ~Tilemap();
        static void generateTransforms(const TilemapData &l_data, TransformContainer &l_transforms);
    protected:
        TilemapData m_data{};
    };
}
