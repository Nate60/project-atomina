#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/TextureBinding.hpp"
#include "util/GLAD/ConvertersGLADImpl.hpp"

namespace ATMA
{

    /**
     * @brief OpenGL specific implementation of Texture
     */
    class ATMA_API TextureBindingGLADImpl: public TextureBinding
    {
    public:
        friend class std::unique_ptr<TextureBindingGLADImpl>;

        // constructor with name and filename of resource
        TextureBindingGLADImpl(const std::string &l_fileName);

        // default deconstructor
        virtual ~TextureBindingGLADImpl();

        /**
         * @brief binds the texture to the GL context
         */
        virtual void bind() override;

        /**
         * @brief unbinds the texture from the GL context
         */
        virtual void unbind() override;

        virtual std::shared_ptr<TextureBinding>
        getSubImage(const Vec2<unsigned int> &l_pos, const Vec2<unsigned int> &l_size) override;
    protected:
        TextureBindingGLADImpl();
    };

}