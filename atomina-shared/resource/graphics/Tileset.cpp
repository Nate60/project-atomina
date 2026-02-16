#include "pch.hpp"
#include <memory>
#include "Tileset.hpp"

namespace ATMA
{
    Tile::Tile() {}

    Tile::Tile(const unsigned int &l_type, const std::shared_ptr<Animation> &l_anim): m_type(l_type), m_anim(l_anim) {}

    Tile::Tile(const Tile &l_other): m_type(l_other.m_type), m_anim(l_other.m_anim) {}

    Tile::Tile(Tile &&l_other): m_type(std::move(l_other.m_type)), m_anim(std::move(l_other.m_anim)) {}

    Tile::~Tile() {}

    void Tile::operator=(const Tile &l_other)
    {
        m_type = l_other.m_type;
        m_anim = l_other.m_anim;
    }

    void Tile::operator=(Tile &&l_other)
    {
        m_type = std::move(l_other.m_type);
        m_anim = std::move(l_other.m_anim);
    }

    const unsigned int &Tile::type() const
    {
        return this->m_type;
    }

    const std::shared_ptr<Animation> &Tile::animation() const
    {
        return this->m_anim;
    }

    Tileset::Tileset(const std::unordered_map<unsigned int, Tile> &l_tiles): LoadedResource(), m_tiles(l_tiles) {}

    Tileset::~Tileset() {}
}
