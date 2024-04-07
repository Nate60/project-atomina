#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/Resource.hpp"
#include "util/Path.hpp"
#include "render/GLTexture.hpp"

namespace ATMA
{

    class ATMA_API Font: public Resource
    {
    public:
        Font(const std::string &l_name);
        Font(const std::string &l_name, const Path &l_path);
        virtual ~Font();
        const std::shared_ptr<GLTexture> m_fontTexture;
        static const int constexpr GLYPH_SIZE = 32;
        static const float constexpr SHEET_SIZE_X = GLYPH_SIZE * 11;
        static const float constexpr SHEET_SIZE_Y = GLYPH_SIZE * 12;
        static const float constexpr GLYPH_SIZE_RATIO_X = GLYPH_SIZE / SHEET_SIZE_X;
        static const float constexpr GLYPH_SIZE_RATIO_Y = GLYPH_SIZE / SHEET_SIZE_Y;
    };

}