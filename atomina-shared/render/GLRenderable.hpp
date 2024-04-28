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
        short m_stackPos{0};
        Vec2<float> m_screenPos{};
        Vec2<float> m_region{};
        Vec2<float> m_srcPos{};
        Vec2<float> m_srcRegion{};
        std::variant<std::shared_ptr<GLTexture>, std::string> m_element{};
        std::shared_ptr<GLShader> m_fragShader{};
        std::shared_ptr<GLShader> m_vertShader{};   


    };

    struct ATMA_API GLRenderableCompare{
        bool operator()(const std::shared_ptr<GLRenderable> &a, const std::shared_ptr<GLRenderable> &b)
        {
            return a->m_stackPos > b->m_stackPos;
        }
    };

}