#pragma once
#include "pch.hpp"
#include "render/GLTexture.hpp"
#include "resource/graphics/Animation.hpp"

namespace ATMA
{
    struct Tile
    {

        Tile();
        Tile(const unsigned int &l_type, const std::shared_ptr<Animation> &l_anim);
        Tile(const Tile &l_other);
        Tile(Tile &&l_other);
        virtual ~Tile();
        void operator=(const Tile &l_other);
        void operator=(Tile &&l_other);
        const unsigned int &type() const;
        const std::shared_ptr<Animation> &animation() const;
    protected:
        unsigned int m_type;
        std::shared_ptr<Animation> m_anim;
    };

    class Tileset: public LoadedResource
    {
    public:
        const std::unordered_map<unsigned int, Tile> m_tiles;

        Tileset(const std::unordered_map<unsigned int, Tile> &m_tiles);

        virtual ~Tileset();
    };
}
