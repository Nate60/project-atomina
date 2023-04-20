#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "math/Vec2.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    /**
     * @brief resource containing pixel data of an image
     */
    class ATMA_API TextureBinding
    {
    public:
        friend class std::unique_ptr<TextureBinding>;

        // constructor with name and filename of resource
        TextureBinding(const std::string &l_fileName);

        // deconstructor
        virtual ~TextureBinding();

        /**
         * @brief binds the texture to the GL context
         */
        virtual void bind() = 0;

        /**
         * @brief unbinds the texture from the GL context
         */
        virtual void unbind() = 0;

        virtual std::shared_ptr<TextureBinding>
        getSubImage(const Vec2<unsigned int> &l_pos, const Vec2<unsigned int> &l_size) = 0;

        /**
         * @brief gets the reference id of the texture in the GL context
         * @return id of the texture
         */
        const unsigned int &getID() const;
    protected:
        TextureBinding();

        int m_width, m_height, m_channels;
        unsigned char *m_data;
        unsigned int m_bindID;
    };

}
