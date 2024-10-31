#pragma once
#include "pch.hpp"
#include "util/Props.hpp"
#include "render/GLSprite.hpp"

namespace ATMA
{
    class GLSpriteDummyImpl: public GLSprite
    {
    public:
        virtual void draw(const Props &l_props);

    };
}