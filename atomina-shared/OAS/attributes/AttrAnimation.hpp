#pragma once
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"
#include "resource/graphics/AnimBase.hpp"
#include "resource/graphics/animation/AnimDefault.hpp"
#include "resource/graphics/SpriteSheet.hpp"

namespace ATMA
{

    class ATMA_API AttrAnimation: public AttrBase
    {
    public:
        AttrAnimation();

        ~AttrAnimation();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        void readIn(std::stringstream &l_stream);

        std::shared_ptr<SpriteSheet> m_spriteSheet{new SpriteSheet{"[null]"}};
        std::unique_ptr<AnimBase> m_animation{new AnimDefault{}};
    };

}