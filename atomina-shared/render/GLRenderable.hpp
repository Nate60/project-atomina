#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "math/Vec2.hpp"
#include "GLTexture.hpp"
#include "GLShader.hpp"
#include "GLBuffer.hpp"

namespace ATMA
{
    /**
     * aggregate for objects to be rendered to the screen
    */
    struct ATMA_API GLRenderable
    {
    public:
        Vec2<float> m_screenPos{};
        Vec2<float> m_region{};
        Vec2<float> m_srcPos{};
        Vec2<float> m_srcRegion{};
        std::shared_ptr<GLTexture> m_texture{};
        std::shared_ptr<GLShader> m_fragShader{};
        std::shared_ptr<GLShader> m_vertShader{};

    };


}