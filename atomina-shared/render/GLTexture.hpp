#pragma once
#include "pch.hpp"
#include "resource/Resource.hpp"
#include "resource/ResourceEnum.hpp"
#include "math/Vec2.hpp"
#include "math/MathFuncs.hpp"
#include "util/Log.hpp"
#include "util/Path.hpp"
#include "GLBuffer.hpp"

namespace ATMA
{

    /**
     * Resource sub-class for texture to allow context to load to unload
     */
    struct Texture: public Resource
    {
    public:
        // constructor defining name, path, width, height, amount of channels, and data
        Texture(
            const std::string &l_name,
            const Path &l_path,
            const int &l_width,
            const int &l_height,
            const int &l_channels,
            unsigned char *l_data
        ):
            Resource(l_name, l_path, ResType(ResourceEnum::Texture)),
            m_width(l_width),
            m_height(l_height),
            m_channels(l_channels),
            m_proj(translationMatrix<float>(0.f, 0.f) * scalingMatrix<float>(l_width, l_height)),
            m_data(l_data)
        {
        }

        // default constructor
        Texture():
            Resource("", Path{""}, ResType(ResourceEnum::Texture)),
            m_width(0),
            m_height(0),
            m_channels(0),
            m_proj(identityMatrix<float>()),
            m_data()
        {
        }

        // Copy Constructor
        Texture(const Texture &l_other):
            Resource(l_other.m_name, l_other.m_path, l_other.m_type),
            m_width(l_other.m_width),
            m_height(l_other.m_height),
            m_channels(l_other.m_channels),
            m_proj(l_other.m_proj),
            m_data(l_other.m_data)
        {
        }

        // Move Constructor
        Texture(Texture &&l_other):
            Resource(std::move(l_other.m_name), std::move(l_other.m_path), std::move(l_other.m_type)),
            m_width(std::move(l_other.m_width)),
            m_height(std::move(l_other.m_height)),
            m_channels(std::move(l_other.m_channels)),
            m_proj(std::move(l_other.m_proj)),
            m_data(std::move(l_other.m_data))
        {
        }

        // Copy Constructor
        void operator=(const Texture &l_other);

        // Move Constructor
        void operator=(Texture &&l_other);

        const int &width() const;
        const int &height() const;
        const int &channels() const;
        const Mat3<float> &proj() const;
        const unsigned char *const data() const;
    protected:
        int m_width;
        int m_height;
        int m_channels;
        Mat3<float> m_proj;
        unsigned char *m_data;
    };

    /**
     * @brief resource containing pixel data of an image
     */
    class GLTexture: public LoadedResource
    {
    public:
        Texture m_texture;

        // copy constructor
        GLTexture(const GLTexture &l_texture);

        // move constructor
        GLTexture(GLTexture &&l_texture);

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

        // copy assignment operator
        void operator=(const GLTexture &l_texture);

        // move assignment operator
        void operator=(GLTexture &&l_texture);

        /**
         * static factory function for creating a GL texture
         * @param l_filePath path to file on system
         * @returns pointer to new created texture for the platform
         */
        static std::shared_ptr<GLTexture> makeTexture(const Texture &l_texture);
    protected:
        // constructor with name and filename of resource
        GLTexture(const Texture &l_texture);
        unsigned int m_bindID;
        std::shared_ptr<VertexBuffer> m_vertBuf;
        std::shared_ptr<IndexBuffer> m_indexBuf;
        std::shared_ptr<VertexArray> m_vertArr;
    };

}
