#pragma once
#include "pch.hpp"
#include "util/Props.hpp"
#include "math/MathFuncs.hpp"
#include "render/GLRenderable.hpp"

namespace ATMA
{
    class GLRenderableDummyImpl: public GLRenderable
    {
    public:
        virtual void draw(const Props &l_props);
    };
}
