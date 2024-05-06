#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/Resource.hpp"
#include "render/GLTexture.hpp"

namespace ATMA{

    /**
     * Wrapper class of the GL Texture so that it can be handled as a resource
    */
    class ATMA_API Texture: public Resource
    {
    public:
        //constructor specifying name of texture
        Texture(const std::string &l_name);

        //constructor specifying name and path to texture image
        Texture(const std::string &l_name, const Path &l_path);

        //deconstructor
        virtual ~Texture();
        const std::shared_ptr<GLTexture> m_self;
    };

}