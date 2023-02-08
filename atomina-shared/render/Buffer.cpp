#include "pch.hpp"
#include "Buffer.hpp"
#include "GLAD/BufferGLADImpl.hpp"

namespace ATMA
{

    IndexBuffer::IndexBuffer(const std::vector<unsigned int> &l_data)
    {

        m_data = l_data;
    }

    IndexBuffer::IndexBuffer()
    {

        m_data = {};
    }

    IndexBuffer::~IndexBuffer() {}

    std::shared_ptr<IndexBuffer> IndexBuffer::makeBuffer(const std::vector<unsigned int> &l_data)
    {
#ifdef ATMA_USE_OPENGL
        return std::make_shared<IndexBufferGLADImpl>(l_data);
#endif
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::makeBuffer()
    {
#ifdef ATMA_USE_OPENGL
        return std::make_shared<IndexBufferGLADImpl>();
#endif
    }

    VertexBuffer::VertexBuffer(const std::vector<float> &l_data): m_data(l_data) {}

    VertexBuffer::VertexBuffer()
    {
        m_data = {};
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::makeBuffer(const std::vector<float> &l_data)
    {
#ifdef ATMA_USE_OPENGL
        return std::make_shared<VertexBufferGLADImpl>(l_data);
#endif
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::makeBuffer()
    {
#ifdef ATMA_USE_OPENGL
        return std::make_shared<VertexBufferGLADImpl>();
#endif
    }

    VertexBuffer::~VertexBuffer() {}

    VertexArray::VertexArray(const std::vector<LayoutElement> &l_elements):
        m_elementSpecs(l_elements)
    {
    }

    VertexArray::VertexArray(const std::initializer_list<LayoutElement> &l_elements)
    {
        for(auto &l_element: l_elements)
            m_elementSpecs.emplace_back(l_element);
    }

    VertexArray::VertexArray()
    {
        m_elementSpecs = {};
    }

    std::shared_ptr<VertexArray> VertexArray::makeBuffer(const std::vector<LayoutElement> &l_list)
    {
#ifdef ATMA_USE_OPENGL
        return std::make_shared<VertexArrayGLADImpl>(l_list);
#endif
    }

    std::shared_ptr<VertexArray> VertexArray::makeBuffer(
        const std::initializer_list<LayoutElement> &l_list
    )
    {
#ifdef ATMA_USE_OPENGL
        return std::make_shared<VertexArrayGLADImpl>(l_list);
#endif
    }

    std::shared_ptr<VertexArray> VertexArray::makeBuffer()
    {
#ifdef ATMA_USE_OPENGL
        return std::make_shared<VertexArrayGLADImpl>();
#endif
    }

    VertexArray::~VertexArray() {}
}