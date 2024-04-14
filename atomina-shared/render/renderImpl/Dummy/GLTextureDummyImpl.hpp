#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLTexture.hpp"

//#include "util/GLAD/ConvertersGLADImpl.hpp"

namespace ATMA
{

    /**
     * @brief Dummy specific implementation of Texture
     */
    class ATMA_API GLTextureDummyImpl: public GLTexture
    {
    public:
        friend class std::unique_ptr<GLTextureDummyImpl>;

        // constructor with name and filename of resource
        GLTextureDummyImpl(const Path &l_filePath);

        // default deconstructor
        virtual ~GLTextureDummyImpl();

        /**
         * @brief binds the texture to the GL context
         */
        virtual void bind() override;

        /**
         * @brief unbinds the texture from the GL context
         */
        virtual void unbind() override;

        /**
         * get an image from within the texture and create a new texture from it
         * @param l_pos position within the texture to begin the region
         * @param l_size dimensions of the region
         * @return new texture made from the parent texture
         */
        virtual std::shared_ptr<GLTexture>
        getSubImage(const Vec2<unsigned int> &l_pos, const Vec2<unsigned int> &l_size) override;
    protected:
        GLTextureDummyImpl();
    };

}