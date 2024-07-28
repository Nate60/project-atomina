#pragma once
#include "pch.hpp"
#include "GLRenderable.hpp"

namespace ATMA
{

    struct GLText: public GLRenderable
    {
    public:
        std::string m_text{};

        static std::shared_ptr<GLText> makeText(
            const std::string &l_text = {},
            const Vec2<float> &l_size = {},
            std::shared_ptr<GLTexture> l_texture = nullptr,
            std::shared_ptr<GLProgram> l_prog = nullptr,
            const Vec2<float> &l_pos = {},
            const short &l_stackPos = {0},
            const float &l_rot = {}
        );
    };

}