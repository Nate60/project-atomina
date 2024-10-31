#pragma once
#include "pch.hpp"
#include "GLRenderable.hpp"

namespace ATMA
{

    struct GLSprite: public GLRenderable
    {
    public:
        Vec2<float> m_selectPos{};
        Vec2<float> m_selectSize{};

        static std::shared_ptr<GLSprite> makeSprite(
            const Vec2<float> &l_selectSize = {},
            const Vec2<float> &l_size = {},
            std::shared_ptr<GLTexture> l_texture = nullptr,
            std::shared_ptr<GLProgram> l_prog = nullptr,
            const Vec2<float> &l_pos = {},
            const Vec2<float> &l_selectPos = {},
            const short &l_stackPos = {0},
            const float &l_rot = {}
        );
    };

}