#pragma once
#include "pch.hpp"
#include "util/Props.hpp"
#include "render/GLText.hpp"

namespace ATMA
{
    class GLTextDummyImpl: public GLText
    {
    public:
        virtual void draw(const Props &l_props);

    };
}