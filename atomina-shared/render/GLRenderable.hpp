#pragma once
#include "pch.hpp"
#include "math/Vec2.hpp"
#include "GLTexture.hpp"
#include "GLProgram.hpp"
#include "util/Props.hpp"
#include "math/MathFuncs.hpp"

namespace ATMA
{
    /**
     * aggregate for objects to be rendered to the screen
     */
    struct GLRenderable
    {
    public:
        short m_stackPos{0};
        float m_rot{};
        Vec2<float> m_size{};
        Vec2<float> m_pos{};
        std::shared_ptr<GLTexture> m_texture = nullptr;
        std::shared_ptr<GLProgram> m_prog = nullptr;

        /**
        * draw call to draw object to render target
        * @param l_props properties to define how draw is made
        */
        virtual void draw(const Props &l_props) = 0;

        /**
        * factory function to create renderable object
        * @param l_size in world space
        * @param l_texture texture render
        * @param l_prog shader program
        * @param l_pos in world space
        * @param l_stackPos priority in render order
        * @param l_rot rotation in world space
        */
        static std::shared_ptr<GLRenderable> makeRenderable(
            const Vec2<float> &l_size = {},
            std::shared_ptr<GLTexture> l_texture = nullptr,
            std::shared_ptr<GLProgram> l_prog = nullptr,
            const Vec2<float> &l_pos = {},
            const short &l_stackPos = {0},
            const float &l_rot = {}
        );
    };

    /**
    * Comparable for defining how to compare renderables with respect to priority queues
    */
    struct GLRenderableCompare
    {
        bool operator()(const std::shared_ptr<GLRenderable> &a, const std::shared_ptr<GLRenderable> &b);
    };

}