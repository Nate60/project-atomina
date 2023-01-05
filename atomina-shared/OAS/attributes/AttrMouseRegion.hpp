#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace ATMA
{
    /**
     * Attribute that contains the region for mouse events for an object
     */
    class ATMA_API AttrMouseRegion: public AttrBase
    {
    public:
        //default constructor
        AttrMouseRegion();

        //deconstructor
        ~AttrMouseRegion();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream);

        sf::Rect<int> m_region{};
    };
}