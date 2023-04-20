#include "pch.hpp"
#include "Texture.hpp"

namespace ATMA
{

    // constructor specifying name
    Texture::Texture(const std::string &l_name): Resource(l_name)
    {
#ifdef ATMA_USE_OPENGL
        m_self = std::make_shared<TextureBindingGLADImpl>(ATConst::DEFAULT_TEXTURE_PATH);
#endif

        m_vertexArray = VertexArray::makeBuffer({
            {2, 8, 0}, //  pos (x,y)
            {4, 8, 2}, //  colour (r,g,b,a)
            {2, 8, 6}  // 2D Texture pos (x,y)
        });

        m_vertexBuffer = VertexBuffer::makeBuffer({1.f,  1.f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                                                   1.f,  -1.f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                                   -1.f, -1.f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                                                   -1.f, 1.f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f});

        m_indexBuffer = IndexBuffer::makeBuffer({0, 1, 2, 0, 2, 3});

        m_vertexArray->bind();
        m_indexBuffer->bind();
        m_vertexBuffer->bind();
        m_vertexArray->bindLayout();
        m_self->bind();
    }

    // constructor specifying name and filename;
    Texture::Texture(const std::string &l_name, const std::string &l_filename):
        Resource(l_name, l_filename)
    {
#ifdef ATMA_USE_OPENGL
        m_self = std::make_shared<TextureBindingGLADImpl>(l_filename);
#endif

        m_vertexArray = VertexArray::makeBuffer({
            {2, 8, 0}, //  pos (x,y)
            {4, 8, 2}, //  colour (r,g,b,a)
            {2, 8, 6}  // 2D Texture pos (x,y)
        });

        m_vertexBuffer = VertexBuffer::makeBuffer({1.f,  1.f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                                                   1.f,  -1.f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                                   -1.f, -1.f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                                                   -1.f, 1.f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f});

        m_indexBuffer = IndexBuffer::makeBuffer({0, 1, 2, 0, 2, 3});

        m_vertexArray->bind();
        m_indexBuffer->bind();
        m_vertexBuffer->bind();
        m_vertexArray->bindLayout();
        m_self->bind();
    }

    Texture::Texture(std::shared_ptr<TextureBinding> l_self): Resource("subimage")
    {
        m_self = l_self;

        m_vertexArray = VertexArray::makeBuffer({
            {2, 8, 0}, //  pos (x,y)
            {4, 8, 2}, //  colour (r,g,b,a)
            {2, 8, 6}  // 2D Texture pos (x,y)
        });

        m_vertexBuffer = VertexBuffer::makeBuffer({1.f,  1.f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                                                   1.f,  -1.f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                                   -1.f, -1.f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                                                   -1.f, 1.f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f});

        m_indexBuffer = IndexBuffer::makeBuffer({0, 1, 2, 0, 2, 3});

        m_vertexArray->bind();
        m_indexBuffer->bind();
        m_vertexBuffer->bind();
        m_vertexArray->bindLayout();
        m_self->bind();
    }

    void Texture::bind()
    {
        m_self->bind();
        m_vertexArray->bind();
        m_indexBuffer->bind();
    }

    void Texture::unbind()
    {
        m_self->unbind();
    }

    std::shared_ptr<Texture>
    Texture::getSubImage(const Vec2<unsigned int> &l_pos, const Vec2<unsigned int> &l_size)
    {
        return std::make_shared<Texture>(m_self->getSubImage(l_pos, l_size));
    }

    const unsigned int &Texture::getBindID() const
    {
        return m_self->getID();
    }
}