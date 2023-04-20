#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLAD/TextureBindingGLADImpl.hpp"
#include "resource/Resource.hpp"
#include "util/ATConst.hpp"
#include "render/Buffer.hpp"

namespace ATMA
{

    class ATMA_API Texture: public Resource
    {
    public:
        // constructor specifying name
        Texture(const std::string &l_name);

        // constructor specifying name and filename;
        Texture(const std::string &l_name, const std::string &l_filename);

        Texture(std::shared_ptr<TextureBinding> l_self);

        void bind();

        void unbind();

        std::shared_ptr<Texture>
        getSubImage(const Vec2<unsigned int> &l_pos, const Vec2<unsigned int> &l_size);

        /**
         * @brief gets the reference id of the shader from the GL context
         * @return id of the shader
         */
        const unsigned int &getBindID() const;
    protected:
        std::shared_ptr<TextureBinding> m_self;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
        std::shared_ptr<VertexBuffer> m_vertexBuffer;
        std::shared_ptr<VertexArray> m_vertexArray;
    };

}