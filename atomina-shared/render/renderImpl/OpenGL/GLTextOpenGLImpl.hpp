#pragma once
#include "pch.hpp"
#include "util/Props.hpp"
#include "render/GLText.hpp"
#include "math/MathFuncs.hpp"

namespace ATMA
{
    class GLTextOpenGLImpl: public GLText
    {
    public:
        virtual void draw(const Props &l_props);
    };
}