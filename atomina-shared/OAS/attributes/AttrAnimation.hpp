#pragma once
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"
#include "resource/graphics/Animation.hpp"

namespace ATMA
{

    /**
     * An Attribute that holds the members of an object required to animate a sprite
     */
    class AttrAnimation: public AttrBase
    {
    public:
        // default constructor
        AttrAnimation();

        // deconstructor
        virtual ~AttrAnimation();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream);

        std::shared_ptr<Animation> m_self = nullptr;
    };

}
