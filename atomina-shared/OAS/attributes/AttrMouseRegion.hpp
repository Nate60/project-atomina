#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace ATMA
{

    class ATMA_API AttrMouseRegion: public AttrBase
    {
    public:
        AttrMouseRegion();

        ~AttrMouseRegion();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        void readIn(std::stringstream &l_stream);

        sf::Rect<int> m_region{};
    };
}