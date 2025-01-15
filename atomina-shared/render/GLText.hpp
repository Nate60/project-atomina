#pragma once
#include "pch.hpp"
#include "GLRenderable.hpp"

namespace ATMA
{
    /**
    * Text variation of sprite that render strings to render target
    */
    struct GLText: public GLRenderable
    {
    public:
        std::string m_text{};

        /**
        * factory function to make renderable text
        * @param l_text string to render
        * @param l_size size of text in worldspace
        * @param l_texture source font texture
        * @param l_prog shader program
        * @param l_pos position of text in worldspace
        * @param l_stackPos priority in render queue
        * @param l_rot rotation of text in worldspace
        */
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