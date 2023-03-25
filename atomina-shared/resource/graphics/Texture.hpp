#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/Resource.hpp"
#include "math/Vec2.hpp"

namespace ATMA
{

    /**
     * @brief resource containing pixel data of an image
     */
    class ATMA_API Texture: public Resource
    {
    public:
        // constructor with name
        Texture(const std::string &l_name);

        // constructor with name and filename of resource
        Texture(const std::string &l_name, const std::string &l_fileName);

        // deconstructor
        virtual ~Texture();

        /**
         * @brief binds the texture to the GL context
         */
        virtual void bind();

        /**
         * @brief unbinds the texture from the GL context
         */
        virtual void unbind();

        virtual std::shared_ptr<Texture>
        getSubImage(const Vec2<unsigned int> &l_pos, const Vec2<unsigned int> &l_size);

        /**
         * @brief gets the reference id of the texture in the GL context
         * @return id of the texture
         */
        const unsigned int &getID() const;
    protected:
        int m_width, m_height, m_channels;
        unsigned char *m_data;
        unsigned int m_bindID;
    };

}
