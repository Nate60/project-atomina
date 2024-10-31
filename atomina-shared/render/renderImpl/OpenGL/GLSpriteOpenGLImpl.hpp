#pragma once
#include "pch.hpp"
#include "util/Props.hpp"
#include "render/GLSprite.hpp"
#include "math/MathFuncs.hpp"

namespace ATMA
{
    class GLSpriteOpenGLImpl: public GLSprite
    {
    public:
        virtual void draw(const Props &l_props);

    };
}