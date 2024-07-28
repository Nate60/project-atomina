#pragma once
#include "pch.hpp"
#include "resource/Resource.hpp"
#include "resource/ResourceEnum.hpp"
#include "math/Vec2.hpp"
#include "util/Log.hpp"
#include "util/Path.hpp"
#include "GLBuffer.hpp"

namespace ATMA
{

    struct Texture: public Resource
    {
    public:
        Texture(
            const std::string &l_name,
            const Path &l_path,
            const int &l_width,
            const int &l_height,
            const int &l_channels,
            const unsigned char *l_data
        ):
            Resource(l_name, l_path, ResType(ResourceEnum::Texture)),
            m_width(l_width), 
            m_height(l_height),
            m_channels(l_channels),
            m_data(l_data)
        {

        }

        Texture() :
            Resource("", Path{ "" }, ResType(ResourceEnum::Texture)),
            m_width(0),
            m_height(0),
            m_channels(0),
            m_data()
        {

        }

        const int m_width;
        const int m_height;
        const int m_channels;
        const unsigned char *m_data;

    };

    /**
     * @brief resource containing pixel data of an image
     */
    class GLTexture: public LoadedResource
    {
    public:
        friend class std::unique_ptr<GLTexture>;

        // deconstructor
        virtual ~GLTexture();

        /**
         * @brief binds the texture to the GL context
         */
        virtual void bind() = 0;

        /**
         * @brief unbinds the texture from the GL context
         */
        virtual void unbind() = 0;

        /**
         * Create a sub texture from the current texture
         * @param l_pos starting region coordinates
         * @param l_size size of region
         * @returns new Texture from current texture
        */
        virtual std::shared_ptr<GLTexture>
        getSubImage(const Vec2<unsigned int> &l_pos, const Vec2<unsigned int> &l_size) = 0;

        /**
         * @brief gets the reference id of the texture in the GL context
         * @return id of the texture
         */
        const unsigned int &getID() const;

        /**
         * static factory function for creating a GL texture
         * @param l_filePath path to file on system
         * @returns pointer to new created texture for the platform
        */
        static std::shared_ptr<GLTexture> makeTexture(const Texture &l_texture);
    protected:

        // constructor with name and filename of resource
        GLTexture(const Texture &l_texture);
        const Texture m_texture;
        unsigned int m_bindID;
        std::shared_ptr<VertexBuffer> m_vertBuf;
        std::shared_ptr<IndexBuffer> m_indexBuf;
        std::shared_ptr<VertexArray> m_vertArr;
    };

}