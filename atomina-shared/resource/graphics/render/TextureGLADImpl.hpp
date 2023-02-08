#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/graphics/Texture.hpp"

namespace ATMA
{

    /**
     * @brief OpenGL specific implementation of Texture
     */
    class ATMA_API TextureGLADImpl: public Texture
    {
    public:
        // constructor specifying name
        TextureGLADImpl(const std::string &l_name);

        // constructor with name and filename of resource
        TextureGLADImpl(const std::string &l_name, const std::string &l_fileName);

        // default deconstructor
        virtual ~TextureGLADImpl();

        /**
         * @brief binds the texture to the GL context
         */
        virtual void bind() override;

        /**
         * @brief unbinds the texture from the GL context
         */
        virtual void unbind() override;
    };

}