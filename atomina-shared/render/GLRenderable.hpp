#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "math/Vec2.hpp"
#include "GLTexture.hpp"
#include "GLShader.hpp"

namespace ATMA
{
    struct ATMA_API Renderable
    {
        Vec2<int> m_screenPos{};
        Vec2<int> m_region{};
        std::shared_ptr<GLTexture> m_texture{};
        std::shared_ptr<GLShader> m_fragShader{};
        std::shared_ptr<GLShader> m_vertShader{};
    };

}