#pragma once
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"
#include "resource/graphics/AnimBase.hpp"
#include "resource/graphics/animation/AnimDefault.hpp"
#include "resource/graphics/SpriteSheet.hpp"

namespace ATMA
{

    /**
     * Attribute that holds members pertaining to an animation and its related
     * sprite sheet for an object 
     */
    class ATMA_API AttrAnimation: public AttrBase
    {
    public:

        //default constructor
        AttrAnimation();

        //deconstructor
        ~AttrAnimation();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream);

        std::shared_ptr<SpriteSheet> m_spriteSheet{new SpriteSheet{"[null]"}};
        std::unique_ptr<AnimBase> m_animation{new AnimDefault{}};
    };

}