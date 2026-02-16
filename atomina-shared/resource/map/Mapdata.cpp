#include "pch.hpp"
#include "resource/Resource.hpp"
#include "Mapdata.hpp"

namespace ATMA
{

    Mapdata::Mapdata(
        const std::vector<unsigned int> &l_data,
        const unsigned int &l_width,
        const Vec2<unsigned int> &l_size
    ):
        LoadedResource(),
        m_width(l_width),
        m_data(l_data),
        m_tilesize(l_size)
    {
    }

    Mapdata::~Mapdata() {}

    const unsigned int &Mapdata::width() const
    {
        return this->m_width;
    }

    const std::vector<unsigned int> &Mapdata::data() const
    {
        return this->m_data;
    }

    const Vec2<unsigned int> &Mapdata::tilesize() const
    {
        return this->m_tilesize;
    }

}
