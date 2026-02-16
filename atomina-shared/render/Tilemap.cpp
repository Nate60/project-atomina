#include "pch.hpp"
#include "render/Renderable.hpp"
#include "Tilemap.hpp"

namespace ATMA
{

    Tilemap::Tilemap(): Renderable(), m_data() {}

    Tilemap::~Tilemap() {}

    Tilemap::Tilemap(const TilemapData &l_data): Renderable(), m_data(l_data)
    {
        generateTransforms(m_data, *this);
    }

    void Tilemap::generateTransforms(const TilemapData &l_data, TransformContainer &l_transforms)
    {
        l_transforms.clear();
        float xAdv = 0.f;
        float yAdv = 0.f;
        for(auto itr = l_data.m_map->data().begin(); itr != l_data.m_map->data().end(); itr++)
        {
            Transform tt{};
            Vec2<unsigned int> m_sheetElementSize = {32, 32};
            // select character
            tt.m_selectSize = static_cast<Vec2<float>>(m_sheetElementSize);
            unsigned int row = *itr % (l_data.m_sheetWidth / m_sheetElementSize.x);
            unsigned int column = *itr / (l_data.m_sheetWidth / m_sheetElementSize.y);
            tt.m_selectPos = Vec2<float>{
                static_cast<float>(row * m_sheetElementSize.x), static_cast<float>(column * m_sheetElementSize.y)
            };
            // assume origin is top left
            tt.m_pos = Vec2<float>{l_data.m_pos.x + xAdv, l_data.m_pos.y + yAdv};
            tt.m_size = static_cast<const Vec2<float>>(l_data.m_map->tilesize());
            l_transforms.emplace_back(std::make_pair(nullptr, tt));
            xAdv += static_cast<float>(l_data.m_map->tilesize().x);
            if(xAdv >= l_data.m_map->width() * l_data.m_map->tilesize().x)
            {
                xAdv = 0;
                yAdv += static_cast<float>(l_data.m_map->tilesize().y);
            }
        }
    }

}
