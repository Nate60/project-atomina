#pragma once
#include "pch.hpp"
#include "GLRenderable.hpp"

namespace ATMA
{

    /**
     * aggregate that defines a renderable object that is a
     * sub image of a texture
     */
    struct GLSprite: public GLRenderable
    {
    public:
        Vec2<float> m_selectPos{};
        Vec2<float> m_selectSize{};

        /**
         * factory function to create a sprite
         * @param l_selectSize size of region from source texture
         * @param l_size size of sprite in worldspace
         * @param l_texture texture to render
         * @param l_prog shader program
         * @param l_pos position of sprite in worldspace
         * @param l_selectPos position of region from source texture
         * @param l_stackPos priority in render queue
         * @param l_rot rotation of sprite in worldspace
         */
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