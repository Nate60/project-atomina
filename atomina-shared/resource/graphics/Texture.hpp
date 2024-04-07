#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/Resource.hpp"
#include "render/GLTexture.hpp"

namespace ATMA{

    class ATMA_API Texture: public Resource
    {
        public:
        Texture(const std::string &l_name);
        Texture(const std::string &l_name, const Path &l_path);
        virtual ~Texture();
        const std::shared_ptr<GLTexture> m_self;
    };

}