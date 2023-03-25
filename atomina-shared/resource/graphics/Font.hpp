#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/Resource.hpp"
#include "resource/graphics/render/TextureGLADImpl.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    class ATMA_API Font: public Resource
    {
    public:
        // constructor specifying name
        Font(const std::string &l_name);

        // constructor specifying name and filename;
        Font(const std::string &l_name, const std::string &l_filename);

        void bindCharacter(const char &l_character);

        virtual ~Font();
    protected:
        std::unordered_map<char, std::shared_ptr<Texture>> m_characters{};
    };

}