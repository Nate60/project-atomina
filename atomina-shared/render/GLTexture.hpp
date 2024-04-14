#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "math/Vec2.hpp"
#include "util/Log.hpp"
#include "util/Path.hpp"
#include "GLBuffer.hpp"

namespace ATMA
{

    /**
     * @brief resource containing pixel data of an image
     */
    class ATMA_API GLTexture
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
        static std::shared_ptr<GLTexture> makeTexture(const Path &l_filePath);
    protected:
        GLTexture();

        // constructor with name and filename of resource
        GLTexture(const Path &l_filePath);
        int m_width, m_height, m_channels;
        unsigned char *m_data;
        unsigned int m_bindID;
        std::shared_ptr<VertexBuffer> m_vertBuf;
        std::shared_ptr<IndexBuffer> m_indexBuf;
        std::shared_ptr<VertexArray> m_vertArr;
    };

}