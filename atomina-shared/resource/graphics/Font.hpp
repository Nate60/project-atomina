#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/Resource.hpp"
#include "util/Path.hpp"
#include "render/GLTexture.hpp"

namespace ATMA
{

    /**
     * Special kind of texture that is indexed to text characters
     * to make drawing text easier
    */
    class ATMA_API Font: public Resource
    {
    public:
        //Constructor specifying name of font
        Font(const std::string &l_name);

        //Constructor specifying name of font and path to font image
        Font(const std::string &l_name, const Path &l_path);

        //deconstructor
        virtual ~Font();

        
        const std::shared_ptr<GLTexture> m_fontTexture;
        static const int constexpr GLYPH_SIZE = 32;
        static const float constexpr SHEET_SIZE_X = GLYPH_SIZE * 11;
        static const float constexpr SHEET_SIZE_Y = GLYPH_SIZE * 12;
        static const float constexpr GLYPH_SIZE_RATIO_X = GLYPH_SIZE / SHEET_SIZE_X;
        static const float constexpr GLYPH_SIZE_RATIO_Y = GLYPH_SIZE / SHEET_SIZE_Y;
    };

}